function RptGunlukKasaCtrl($scope,$window,db)
{
    function InitIslemGrid()
    {
        $("#TblIslem").jsGrid
        ({
            width: "100%",
            height: "350px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.IslemListe,
            fields: 
            [
                {
                    name: "TIPADI",
                    title: "TİPİ",
                    type: "text",
                    align: "center",
                    width: 75
                },
                {
                    name: "TIP",
                    type: "number",
                    align: "center",
                    width: 100
                },
                {
                    name: "TUTAR",
                    type: "number",
                    align: "center",
                    width: 75
                }
            ]
        });
    }
    $scope.Init = function()
    {   
        gtag('config', 'UA-12198315-15', 
        {
            'page_title' : 'GunlukKasa',
            'page_path': '/GunlukKasa',
            'user_id' : 'UserParam.Kullanici'
        });

        InitIslemGrid();
        
        $scope.Firma = $window.sessionStorage.getItem('Firma');
        UserParam = Param[$window.sessionStorage.getItem('User')];

        $scope.IlkTarih = moment(new Date()).format("DD.MM.YYYY");
        $scope.SonTarih = moment(new Date()).format("DD.MM.YYYY");
        $scope.Sube = "0";
        $scope.GenelToplam = 0;

        $scope.IslemListe = [];
        $scope.SubeListe = [];

        db.FillCmbDocInfo($scope.Firma,'CmbDepoGetir',function(data)
        {
            $scope.SubeListe = data; 
            
            if(UserParam.PosSatis.Sube == 0)
            {
                $scope.Sube = data[0].KODU.toString();
            }
            else
            {   
                $scope.Sube = UserParam.PosSatis.Sube;
                $scope.SubeLock = true;
            }
        });

        if(UserParam.MagazaRaporları == true)
        {
            $scope.DivGenelToplam = true;
        }
        else
        {
            $scope.DivGenelToplam = false;
        }
    }
    $scope.BtnGetir = function()
    {
        var TmpQuery = 
        {
            db : '{M}.' + $scope.Firma,
            query:  "SELECT " +
                    "CASE WHEN EVRAKTIP = 0 THEN 'ÖDEME' WHEN EVRAKTIP = 1 THEN 'TEDİYE' END AS TIPADI, " +
                    "EVRAKTIP AS EVRAKTIP, " +
                    "MKODU AS KODU, " +
                    "ISNULL((SELECT cari_unvan1 FROM CARI_HESAPLAR WHERE cari_kod = MKODU),'') AS CARIADI, " +
                    "CASE WHEN TIP = 0 THEN " +
                    "'NAKİT' " +
                    "WHEN TIP = 1 THEN " +
                    "'KREDİ KARTI' " +
                    "WHEN TIP = 2 THEN " +
                    "'AÇIK HESAP' " +
                    "END AS TIP, " +
                    "CAST(SUM(TUTAR) AS decimal(10,2)) AS TUTAR " +
                    "FROM TERP_POS_TAHSILAT WHERE SUBE = @SUBE AND TARIH >= @ILKTARIH AND TARIH <= @SONTARIH " +
                    "GROUP BY MKODU,TIP,EVRAKTIP",
            param:  ['SUBE','ILKTARIH','SONTARIH'],
            type:   ['int','date','date'],
            value:  [$scope.Sube,$scope.IlkTarih,$scope.SonTarih]
        }

        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.IslemListe = Data;
            $("#TblIslem").jsGrid({data : $scope.IslemListe});
            $scope.GenelToplam = db.SumColumn($scope.IslemListe,"TUTAR","EVRAKTIP = 0") - db.SumColumn($scope.IslemListe,"TUTAR","EVRAKTIP = 1");
        });
    }
    $scope.ExcelExport = function()
    {
        let ExcelDataListe = [];
        let ExcelHeaderListe = [];

        for(i = 0; i < Object.keys($scope.IslemListe[0]).length; i++)
        {
            let a = {};
            
            a.text = Object.keys($scope.IslemListe[0])[i];
            ExcelHeaderListe.push(a)
        }

        ExcelDataListe.push(ExcelHeaderListe)

        for(i = 0; i < $scope.IslemListe.length; i++)
        {
            let Dizi = [];

            for(m = 0;m < Object.keys($scope.IslemListe[i]).length;m++)
            {
                let b = {};
                b.text = $scope.IslemListe[i][Object.keys($scope.IslemListe[i])[m]]
                Dizi.push(b);
                console.log(Dizi)
            }
            
            ExcelDataListe.push(Dizi)
        }
        console.log(ExcelDataListe)
        var RaporListeData = 
        [
            {
                "sheetName":"Sayfa",
                "data":  ExcelDataListe
            }
        ];
        var options = {
            fileName:"GunlukKasaRapor",
            extension:".xlsx",
            sheetName:"Sayfa",
            fileFullName:"report.xlsx",
            header:true,
            maxCellWidth: 20
        };

        Jhxlsx.export(RaporListeData, options);

        var url ='data.json';
        $.get(url, {},function (data) 
        {
            Jhxlsx.export(data.RaporListeData, data.options);
            db.Connection(function(data)
            {
            });
        })
    }
}