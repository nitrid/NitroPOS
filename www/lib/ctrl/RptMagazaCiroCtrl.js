function RptMagazaCiroCtrl($scope,$window,db)
{
    function InitIslemGrid()
    {
        $("#TblIslem").jsGrid
        ({
            width: "100%",
            height: "600px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            sorting: true,
            paging: true,
            autoload: true,
            
            data : $scope.IslemListe,
            fields: 
            [
                {
                    name: "SIRA",
                    type: "number",
                    align: "center",
                    width: 100
                },
                {
                    name: "SUBEADI",
                    title: "ŞUBE ADI",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "ARATOPLAM",
                    type: "number",
                    align: "center",
                    width: 100
                }, 
                {
                    name: "ISKONTO",
                    type: "number",
                    align: "center",
                    width: 100
                }, 
                {
                    name: "GENELTOPLAM",
                    type: "number",
                    align: "center",
                    width: 100
                }
            ]
        });
    }
    $scope.Init = function()
    {
        InitIslemGrid();
        
        $scope.Firma = $window.sessionStorage.getItem('Firma');
        UserParam = Param[$window.sessionStorage.getItem('User')];

        $scope.IlkTarih = moment(new Date()).format("DD.MM.YYYY");
        $scope.SonTarih = moment(new Date()).format("DD.MM.YYYY");
        $scope.Sube = "";
        $scope.AraToplam = 0;
        $scope.ToplamIndirim = 0;
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
   
    }
    $scope.BtnGetir = function()
    {
        var TmpQuery = 
        {
            db : '{M}.' + $scope.Firma,
            query:  "SELECT " + 
                    "ROW_NUMBER() OVER (ORDER BY SUBE DESC) AS SIRA," +
                    "ISNULL((SELECT dep_adi FROM DEPOLAR WHERE dep_no = SUBE),'') AS SUBEADI, " + 
                    "CAST(SUM(CASE WHEN TIP = 1 THEN MIKTAR * FIYAT ELSE (MIKTAR * FIYAT) * -1 END)  AS decimal(10,2)) AS ARATOPLAM, " + 
                    "CAST(SUM(CASE WHEN TIP = 1 THEN ISKONTO ELSE ISKONTO * -1 END) AS decimal(10,2)) AS ISKONTO, " + 
                    "CAST(((SUM(CASE WHEN TIP = 1 THEN MIKTAR * FIYAT ELSE (MIKTAR * FIYAT) * -1 END)) - SUM(CASE WHEN TIP = 1 THEN ISKONTO ELSE ISKONTO * 1 END)) AS decimal(10,2)) AS GENELTOPLAM " + 
                    "FROM TERP_POS_SATIS WHERE TARIH >= @ILKTARIH AND TARIH <= @SONTARIH AND ((SUBE = @SUBE) OR (@SUBE = '')) AND DURUM IN (1,2) " + 
                    "GROUP BY SUBE ORDER BY SUBE DESC",
            param:  ['SUBE','ILKTARIH','SONTARIH'],
            type:   ['string|10','date','date',],
            value:  [$scope.Sube,$scope.IlkTarih,$scope.SonTarih]
        }

        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.IslemListe = Data;
            $("#TblIslem").jsGrid({data : $scope.IslemListe});
            
            $scope.AraToplam = db.SumColumn($scope.IslemListe,"ARATOPLAM");
            $scope.ToplamIndirim = db.SumColumn($scope.IslemListe,"ISKONTO");
            $scope.GenelToplam = db.SumColumn($scope.IslemListe,"GENELTOPLAM");
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
        var RaporListeData = 
        [
            {
                "sheetName":"Sayfa",
                "data":  ExcelDataListe
            }
        ];
        var options = {
            fileName:"MagazaCiroRapor",
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