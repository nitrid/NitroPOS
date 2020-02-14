function RptGunlukSatisCtrl($scope,$window,db)
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
                    name: "KULLANICI",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "SAAT",
                    type: "number",
                    align: "center",
                    width: 75
                },
                {
                    name: "ADI",
                    type: "text",
                    align: "center",
                    width: 200
                    
                },
                {
                    name: "TIPADI",
                    title: "TİPİ",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "MIKTAR",
                    type: "number",
                    align: "center",
                    width: 75
                },
                {
                    name: "FIYAT",
                    type: "number",
                    align: "center",
                    width: 75
                },
                {
                    name: "TUTAR",
                    type: "number",
                    align: "center",
                    width: 75
                }, 
                {
                    name: "ISKONTO",
                    type: "number",
                    align: "center",
                    width: 75
                }, 
                {
                    name: "KDV",
                    type: "number",
                    align: "center",
                    width: 75
                }, 
                {
                    name: "TOPLAM",
                    type: "number",
                    align: "center",
                    width: 80
                }, 
                {
                    name: "DEPOMIKTAR",
                    type: "number",
                    align: "center",
                    width: 110
                },
                
                {
                    name: "BARKOD",
                    type: "number",
                    align: "center",
                    width: 150
                },
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
        $scope.AraToplam = 0;
        $scope.ToplamIndirim = 0;
        $scope.ToplamKdv = 0;
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
                    "ROW_NUMBER() OVER (ORDER BY RECID DESC) AS SIRA," +
                    "KULLANICI AS KULLANICI, " +
                    "CONVERT(varchar(10), OTARIH, 108) AS SAAT, " +
                    "SKODU AS KODU, " +
                    "RECID AS RECID, " +
                    "BARKOD AS BARKOD, " +
                    "TIP AS TIP, " +
                    "CASE WHEN TIP = 1 THEN 'SATIŞ' WHEN TIP = 2 THEN 'İADE' END AS TIPADI, " +
                    "ISNULL((SELECT sto_isim FROM STOKLAR WHERE sto_kod = SKODU),'') AS ADI, " +
                    "CAST(SUM(MIKTAR) AS decimal(10,2)) AS MIKTAR, " +
                    "CAST(MAX(FIYAT) AS decimal(10,2))  AS FIYAT, " +
                    "CAST(SUM(MIKTAR * FIYAT) AS decimal(10,2)) AS TUTAR, " +
                    "ISNULL((SELECT dbo.fn_DepodakiMiktar (SKODU,@SUBE,CONVERT(VARCHAR(10),GETDATE(),112))),0) AS DEPOMIKTAR, " +
                    "CAST(SUM(ISKONTO) AS decimal(10,2)) AS ISKONTO, " +
                    "ROUND(((SUM(MIKTAR) * MAX(FIYAT)) - SUM(ISKONTO)) * ((SELECT dbo.fn_VergiYuzde (MAX(KDVPNTR))) / 100),4) AS KDV, " +
                    "ROUND(SUM((ROUND((MIKTAR * FIYAT),4) - ROUND(ISKONTO,4)) * (((ROUND((dbo.fn_VergiYuzde (KDVPNTR)),4)) / 100) + 1)),4) AS TOPLAM " +
                    "FROM TERP_POS_SATIS WHERE SUBE = @SUBE AND TARIH >= @ILKTARIH AND TARIH <= @SONTARIH AND DURUM IN (1,2) " +
                    "GROUP BY SKODU,BARKOD,KULLANICI,TIP,OTARIH,RECID ORDER BY RECID DESC",
            param:  ['SUBE','ILKTARIH','SONTARIH'],
            type:   ['int','date','date',],
            value:  [$scope.Sube,$scope.IlkTarih,$scope.SonTarih]
        }

        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.IslemListe = Data;
            $("#TblIslem").jsGrid({data : $scope.IslemListe});
            
            $scope.AraToplam = db.SumColumn($scope.IslemListe,"TUTAR","TIP = 1") - db.SumColumn($scope.IslemListe,"TUTAR","TIP = 2");
            $scope.ToplamIndirim = db.SumColumn($scope.IslemListe,"ISKONTO","TIP = 1") - db.SumColumn($scope.IslemListe,"ISKONTO","TIP = 2");
            $scope.ToplamKdv = db.SumColumn($scope.IslemListe,"KDV","TIP = 1") - db.SumColumn($scope.IslemListe,"KDV","TIP = 2");
            $scope.GenelToplam = db.SumColumn($scope.IslemListe,"TOPLAM","TIP = 1") - db.SumColumn($scope.IslemListe,"TOPLAM","TIP = 2");
        });
    }
    $scope.BtnEnCokSatanlar = function()
    {
        var TmpQuery = 
        {
            db : '{M}.' + $scope.Firma,
            query:  "SELECT " +
                    "ROW_NUMBER() OVER (ORDER BY RECID DESC) AS SIRA," +
                    "MAX(KULLANICI) AS KULLANICI, " +
                    "SKODU AS KODU, " +
                    "BARKOD AS BARKOD, " +
                    "TIP AS TIP, " +
                    "CASE WHEN TIP = 1 THEN 'SATIŞ' WHEN TIP = 2 THEN 'İADE' END AS TIPADI, " +
                    "ISNULL((SELECT sto_isim FROM STOKLAR WHERE sto_kod = SKODU),'') AS ADI, " +
                    "CAST(SUM(MIKTAR) AS decimal(10,2)) AS MIKTAR, " +
                    "CAST(MAX(FIYAT) AS decimal(10,2))  AS FIYAT, " +
                    "CAST(SUM(MIKTAR * FIYAT) AS decimal(10,2)) AS TUTAR, " +
                    "ISNULL((SELECT dbo.fn_DepodakiMiktar (SKODU,@SUBE,CONVERT(VARCHAR(10),GETDATE(),112))),0) AS DEPOMIKTAR, " +
                    "CAST(SUM(ISKONTO) AS decimal(10,2)) AS ISKONTO, " +
                    "CAST(((SUM(MIKTAR) * MAX(FIYAT)) - SUM(ISKONTO)) * ((SELECT dbo.fn_VergiYuzde (MAX(KDVPNTR))) / 100) AS decimal(10,2)) AS KDV, " +
                    "CAST(((SUM(MIKTAR) * MAX(FIYAT)) - SUM(ISKONTO)) * (((SELECT dbo.fn_VergiYuzde (MAX(KDVPNTR))) / 100) + 1) AS decimal(10,2)) AS TOPLAM " +
                    "FROM TERP_POS_SATIS WHERE SUBE = @SUBE AND TARIH >= @ILKTARIH AND TARIH <= @SONTARIH AND DURUM IN (1,2) " +
                    "GROUP BY SKODU,BARKOD,TIP ORDER BY SUM(MIKTAR) DESC",
            param:  ['SUBE','ILKTARIH','SONTARIH'],
            type:   ['int','date','date',],
            value:  [$scope.Sube,$scope.IlkTarih,$scope.SonTarih]
        }

        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.IslemListe = Data;
            $("#TblIslem").jsGrid({data : $scope.IslemListe});

            $scope.AraToplam = db.SumColumn($scope.IslemListe,"TUTAR","TIP = 1") - db.SumColumn($scope.IslemListe,"TUTAR","TIP = 2");
            $scope.ToplamIndirim = db.SumColumn($scope.IslemListe,"ISKONTO","TIP = 1") - db.SumColumn($scope.IslemListe,"ISKONTO","TIP = 2");
            $scope.ToplamKdv = db.SumColumn($scope.IslemListe,"KDV","TIP = 1") - db.SumColumn($scope.IslemListe,"KDV","TIP = 2");
            $scope.GenelToplam = db.SumColumn($scope.IslemListe,"TOPLAM","TIP = 1") - db.SumColumn($scope.IslemListe,"TOPLAM","TIP = 2");
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
            fileName:"GunlukSatisRapor",
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