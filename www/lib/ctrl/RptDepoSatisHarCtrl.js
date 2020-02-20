function RptDepoSatisHarCtrl($scope,$window,db)
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
            fields: 
            [
                {
                    name: "SERI",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "SIRA",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "TARIH",
                    type: "date",
                    align: "center",
                    width: 200
                },
                {
                    name: "MIKTAR",
                    type: "number",
                    align: "center",
                    width: 75
                },
                {
                    name: "TUTAR",
                    title: "TUTAR",
                    type: "text",
                    align: "center",
                    width: 100
                },
                [
                    { 
                        itemTemplate: function(_, item) 
                        {
                            return $("<button type='submit' class='btn btn-primary btn-block btn-sm'></button>").text("Detay")
                                .on("click", function() 
                                {
                                    $scope.BtnDuzenle();
                                    //alert(item.Name);
                                });
                        },
                        width: 50
                    }
                ]       
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
            
            data : $scope.IslemListe,
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [

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
                name: "TARIH",
                type: "date",
                align: "center",
                width: 200
            },
            {
                name: "STOKKOD",
                title: "STOK KODU",
                type: "number",
                align: "center",
                width: 50
            },
            {
                name: "STOKADI",
                title: "STOK ADI",
                type: "number",
                align: "center",
                width: 50
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
            }],
            rowClick: function(args)
            {
                $scope.SonSatisRowClick(args.itemIndex,args.item);
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
                    "sth_evrakno_seri AS SERI, " +
                    "sth_evrakno_sira AS SIRA, " +
                    "CONVERT(NVARCHAR,sth_belge_tarih,104) AS TARIH, " +
                    "sth_stok_kod AS STOKKOD, " +
                    "(SELECT sto_isim AS STOKADI FROM STOKLAR WHERE sth_stok_kod = sto_kod) AS STOKADI," +
                    "(SELECT sfiyat_fiyati FROM STOK_SATIS_FIYAT_LISTELERI WHERE sth_stok_kod = sfiyat_stokkod) as FIYAT," +
                    "sth_miktar AS MIKTAR, " +
                    "sth_tutar AS TUTAR " +
                    "FROM STOK_HAREKETLERI WHERE sth_giris_depo_no = @SUBE AND sth_tip = 2 AND sth_cins = 6 AND sth_evraktip = 15 ",
            param:  ['SUBE'],
            type:   ['int'],
            value:  [$scope.Sube]
        }

        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.IslemListe = Data;
            $("#TblIslem").jsGrid({data : $scope.IslemListe});

        });
    }
    $scope.BtnDuzenle = function()
    {
        $('#MdlSonSatisDetay').modal('show');
    }
    $scope.BtnGeri = function()
    {
        $('#MdlSonSatisDetay').modal('hide');
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
    $scope.SonSatisRowClick = function(pIndex,pItem,pObj)
    {
        if ( SonSatisSelectedRow ) { SonSatisSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = $("#TblSonSatis").jsGrid("rowByItem", pItem);
        
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','red');
        SonSatisSelectedRow = $row;
        $scope.SonSatisListeSelectedIndex = pIndex;
        let SonSatisDetay = pItem;

        
        $scope.Seri = pItem.SERI;
        $scope.Sira = pItem.SIRA;

            $("#TblSonSatisDetay").jsGrid({data : $scope.IslemListe});
        
    }
}