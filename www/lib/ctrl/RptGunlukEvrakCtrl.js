function RptGunlukEvrakCtrl($scope,$window,db)
{   
    let SonSatisSelectedRow = null;

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

            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [
                {
                    name: "KULLANICI",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "SERI",
                    type: "text",
                    align: "center",
                    width: 75
                },
                {
                    name: "SIRA",
                    type: "text",
                    align: "center",
                    width: 75
                },
                {
                    name: "TARIH",
                    type: "number",
                    align: "center",
                    width: 75
                },
                {
                    name: "SAAT",
                    type: "number",
                    align: "center",
                    width: 75
                },
                {
                    name: "TIPADI",
                    title: "TİPİ",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "SATIR",
                    title: "SATIR",
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
            ],
            rowClick: function(args)
            {
                $scope.SonSatisRowClick(args.itemIndex,args.item);
                $scope.$apply();
            }
        });
    }
    function InitSonSatisDetayGrid()
    {
        $("#TblSonSatisDetay").jsGrid({
            responsive: true,
            width: "100%",
            height: "350px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            
            data : $scope.SonSatisDetayList,
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [
            {
                name: "TIP",
                title: "TIP",
                type: "TEXT",
                align: "center",
                width: 75
            },
            {
                name: "SERI",
                title: "SERI",
                type: "TEXT",
                align: "center",
                width: 35
            },
            {
                name: "SIRA",
                title: "SIRA",
                type: "number",
                align: "center",
                width: 35
            },
            {
                name: "MIKTAR",
                title: "MIKTAR",
                type: "number",
                align: "center",
                width: 50
            },
            {
                name: "FIYAT",
                title: "FIYAT",
                type: "number",
                align: "center",
                width: 50
            },
            {
                name: "TUTAR",
                title: "TUTAR",
                type: "number",
                align: "center",
                width: 50
            },
            {
                name: "BARKOD",
                title: "BARKOD",
                type: "number",
                align: "center",
                width: 100
            }],
            rowClick: function(args)
            {
                $scope.$apply();
            }
        });
    }
    $scope.Init = function()
    {
        InitIslemGrid();
        InitSonSatisDetayGrid();
        
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
        

        $scope.SonSatisListeSelectedIndex = 0; 

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
                    "MAX(KULLANICI) AS KULLANICI, " +
                    "MAX(RECID) AS RECID, " +
                    "MAX(TIP) AS TIP, " +
                    "CASE WHEN MAX(TIP) = 1 THEN 'SATIŞ' WHEN MAX(TIP) = 2 THEN 'İADE' END AS TIPADI, " +
                    "SERI AS SERI, " +
                    "SIRA AS SIRA, " +
                    "COUNT(SATIRNO) AS SATIR, " +
                    "CAST(MAX(MIKTAR) AS DECIMAL(10,2)) AS MIKTAR, " +
                    "CAST(SUM(((MIKTAR * FIYAT) - ISKONTO) * (((dbo.fn_VergiYuzde (KDVPNTR)) /100) + 1 ))as DECIMAL(10,2)) AS TUTAR, " +
                    "CONVERT(VARCHAR(10), MAX(OTARIH), 108) AS SAAT, " +
                    "CONVERT(VARCHAR(10), MAX(OTARIH), 104) AS TARIH " +
                    "FROM TERP_POS_SATIS AS PS WHERE SUBE = @SUBE AND TARIH >= @ILKTARIH AND TARIH <= @SONTARIH AND DURUM IN (1,2) " +
                    "GROUP BY SERI,SIRA ORDER BY RECID DESC " ,
            param:  ['SUBE','ILKTARIH','SONTARIH'],
            type:   ['int','date','date',],
            value:  [$scope.Sube,$scope.IlkTarih,$scope.SonTarih]
        }

        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.IslemListe = Data;
            $("#TblIslem").jsGrid({data : $scope.IslemListe});
            $scope.GenelToplam = db.SumColumn($scope.IslemListe,"TUTAR")
            console.log($scope.IslemListe)
        });


    }
    $scope.SonSatisRowClick = function(pIndex,pItem,pObj)
    {
        if ( SonSatisSelectedRow ) { SonSatisSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = $("#TblSonSatis").jsGrid("rowByItem", pItem);
        
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        SonSatisSelectedRow = $row;
        $scope.SonSatisListeSelectedIndex = pIndex;

        let SonSatisDetay = pItem;
        
        db.GetData($scope.Firma,'PosSonSatisDetayGetir',[$scope.Sube,SonSatisDetay.SERI,SonSatisDetay.SIRA],function(PosSonSatisDetay)
        {  
            $scope.SonSatisDetayList = PosSonSatisDetay;
            $("#TblSonSatisDetay").jsGrid({data : $scope.SonSatisDetayList});
        });

        $('#MdlSonSatisDetay').modal('show');
    }
    $scope.BtnGeri = function()
    {
        $('#MdlSonSatisDetay').modal('hide');
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
            fileName:"GunlukEvrakRapor",
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