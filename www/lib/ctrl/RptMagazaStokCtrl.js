function RptMagazaStokCtrl($scope,$window,db)
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
                    name: "KODU",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "ADI",
                    type: "text",
                    align: "center",
                    width: 200
                    
                },
                {
                    name: "ALISFIYAT",
                    title: "ALIŞ FİYATI",
                    type: "number",
                    align: "center",
                    width: 110
                },
                {
                    name: "SATISFIYAT",
                    title: "SATIŞ FİYATI",
                    type: "number",
                    align: "center",
                    width: 110
                },
                {
                    name: "DEPOMIKTAR",
                    title: "DEPO MİKTAR",
                    type: "number",
                    align: "center",
                    width: 110
                }, 
                {
                    name: "ALISENVANTER",
                    title : "ALIŞ ENVANTER",
                    type: "number",
                    align: "center",
                    width: 110
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
        $scope.Sube = "0";
        $scope.AlisEnvanter = 0;

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
                    "sto_kod AS KODU, " + 
                    "sto_isim AS ADI, " + 
                    "ISNULL((SELECT TOP 1 ROUND(sfiyat_fiyati,2) FROM STOK_SATIS_FIYAT_LISTELERI WHERE sfiyat_stokkod = sto_kod AND sfiyat_deposirano = 0 AND sfiyat_listesirano = 3),0) AS ALISFIYAT, " + 
                    "ISNULL((SELECT TOP 1 ROUND(sfiyat_fiyati,2) FROM STOK_SATIS_FIYAT_LISTELERI WHERE sfiyat_stokkod = sto_kod AND sfiyat_deposirano = 0 AND sfiyat_listesirano = 1),0) AS SATISFIYAT, " + 
                    "(SELECT dbo.fn_DepodakiMiktar(sto_kod,@SUBE,GETDATE())) - " + 
                    "ISNULL((SELECT SUM(CASE WHEN TIP = 1 THEN MIKTAR ELSE MIKTAR * -1 END) FROM TERP_POS_SATIS WHERE SKODU = sto_kod AND SUBE = @SUBE AND DURUM = 1),0) AS DEPOMIKTAR, " + 
                    "((SELECT dbo.fn_DepodakiMiktar(sto_kod,@SUBE,GETDATE())) - ISNULL((SELECT SUM(CASE WHEN TIP = 1 THEN MIKTAR ELSE MIKTAR * -1 END) FROM TERP_POS_SATIS WHERE SKODU = sto_kod AND SUBE = @SUBE AND DURUM = 1),0)) " + 
                    "* ISNULL((SELECT TOP 1 ROUND(sfiyat_fiyati,0) FROM STOK_SATIS_FIYAT_LISTELERI WHERE sfiyat_stokkod = sto_kod AND sfiyat_deposirano = 0 AND sfiyat_listesirano = 3),0) AS ALISENVANTER " + 
                    "FROM STOKLAR " + 
                    "WHERE (SELECT dbo.fn_DepodakiMiktar(sto_kod,@SUBE,GETDATE())) > 0",
            param:  ['SUBE'],
            type:   ['string|10'],
            value:  [$scope.Sube]
        }

        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.IslemListe = Data;
            $("#TblIslem").jsGrid({data : $scope.IslemListe});
            
            $scope.AlisEnvanter = db.SumColumn($scope.IslemListe,"ALISENVANTER");
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
            fileName:"MagazaStokRapor",
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