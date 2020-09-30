function Pos($scope,$window,$rootScope,db)
{
    let IslemSelectedRow = null;
    let CariSelectedRow = null;
    let StokSelectedRow = null;
    let BarkodSelectedRow = null;
    let ParkIslemSelectedRow = null;
    let TahIslemSelectedRow = null;
    let SonSatisSelectedRow = null;
    let FocusBarkod = true;
    let FocusAraToplam = false;
    let FocusMusteri = false;
    let FocusStok = false;
    let FocusMiktarGuncelle = false;
    let FocusFiyatGuncelle = false;
    let FocusKartOdeme = false;
    let FocusYetkiliSifre = false;
    let FocusKasaSifre = false;
    let FocusAvans = false;
    let FirstKey = false;
    let UserParam = null;

    $('#MdlAraToplam').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusFiyatGuncelle = false;
        FocusAvans = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
        FocusKartOdeme = false;
    });
    $('#MdlMusteriListele').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusFiyatGuncelle = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
        FocusAvans = false;
        FocusKartOdeme = false;
    });
    $('#MdlStokListele').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusFiyatGuncelle = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
        FocusAvans = false;
        db.SafeApply($scope,function()
        {
            $scope.TxtBarkod = "";
        })
        FocusKartOdeme = false;
    });
    $('#MdlMiktarGuncelle').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusKartOdeme = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
        FocusAvans = false;
        FocusFiyatGuncelle = false;
    });
    $('#MdlFiyatGuncelle').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
        FocusKartOdeme = false;
        FocusAvans = false;
        FocusFiyatGuncelle = false;
    });
    $('#MdlKartOdeme').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusFiyatGuncelle = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
        FocusAvans = false;
        FocusKartOdeme = false;
    });
    $('#MdlParaUstu').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusFiyatGuncelle = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
        FocusAvans = false;
        FocusKartOdeme = false;
    });
    $('#MdlYetkiliGiris').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusFiyatGuncelle = false;
        FocusAvans = false;
        FocusKartOdeme = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
    });
    $('#MdlKasaSifre').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusFiyatGuncelle = false;
        FocusAvans = false;
        FocusKartOdeme = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
    });
    $('#MdlAvans').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusKartOdeme = false;
        FocusYetkiliSifre = false;
        FocusKasaSifre = false;
        FocusFiyatGuncelle = false;
        FocusAvans = false;
        $scope.TxtYetkiliSifre = "";
    });
    $('#MdlPluEdit').on('hide.bs.modal', function () 
    {
        FocusBarkod = true;
        FocusAraToplam = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusMiktarGuncelle = false;
        FocusKartOdeme = false;
        FocusYetkiliSifre = false;
        FocusFiyatGuncelle = false;
        FocusAvans = false;
        FocusKasaSifre = false;
        $scope.DivPlu = false;
        $scope.PluGrupAdi = "";
        $scope.PluStokKod = "";
        $scope.Index = "";
    });

    if(typeof require != 'undefined')
    {
        $("#MdlIngenicoEslesme").modal("show");  
        db.Ingenico.Init();

        //BURAYA TEKRAR BAKILACAK (CALLBACK DESTROY)
        db.CardPayment.On("PaymentEvent",function(pData)
        {
            if(pData.tag == "response")
            {
                if(JSON.parse(pData.msg).transaction_result != 0)
                {
                    $("#MdlKartYukleniyor").modal("hide"); 
                    alertify.confirm('Ödeme gerçekleşmedi', function()
                    {
                        $("#MdlKartYukleniyor").modal("show");
                    });
                }
                else
                {
                    $("#MdlKartYukleniyor").modal("hide");

                    $scope.PosTahInsert(()=>
                    {
                        if($scope.TahKalan > 0)
                        {
                            $scope.BtnAraToplam();
                        }
                    });
                }
            }
        });

        db.Ingenico.On("IngenicoEvent",function(pData)
        {
            if(pData.tag == "PING")
            {
                if(pData.msg != "CONNECTED")
                {
                    $scope.TxtOkcMesaj = "Bağlantı Başarısız.";
                    $scope.BtnTxtOkcEslesme = "Tekrar";
                }
            }
            else if(pData.tag == "PAIRING")
            {
                if(pData.msg == "SUCCES")
                {
                    $("#MdlIngenicoEslesme").modal("hide");  
                }
                else
                {
                    $scope.TxtOkcMesaj = "Eşleşme Başarısız.";
                    $scope.BtnTxtOkcEslesme = "Tekrar";
                }
            }
           console.log(pData)
        });
    }
    $rootScope.LoadingShow = function() 
    {
        $("#loading").show();
    }
    $rootScope.LoadingHide = function() 
    {
        $("#loading").hide();
    }
    $rootScope.MessageBox = function(pMsg)
    {
        alertify.alert(pMsg);
    }
    function Init()
    {
        UserParam = Param[$window.sessionStorage.getItem('User')];                
        $scope.Firma = 'NITROGENPOS'
        $scope.Seri = "";
        $scope.TahSeri = "";
        $scope.Sira = 0;
        $scope.TahSira = 0;
        $scope.EvrakTip = 0;
        $scope.CariKodu = "";
        $scope.CariAdi = "";
        $scope.Tarih = new Date().toLocaleDateString('tr-TR',{ year: 'numeric', month: 'numeric', day: 'numeric' });
        $scope.Sube = "0";
        $scope.TxtBarkod = "";
        $scope.AraToplam = 0;
        $scope.ToplamKdv = 0;
        $scope.ToplamIskonto = 0;
        $scope.ToplamKalan = 0;
        $scope.ToplamFisIskonto = 0;
        $scope.GenelToplam = 0;
        $scope.ToplamMiktar = 0;
        $scope.ToplamSatir = 0;
        $scope.ParkIslemSayisi = 0;
        $scope.CiktiTip = 1;
        $scope.TxtYetkiliSifre = "";
        $scope.TxtAvans = 0;
        $scope.AvansTip = 0;
        $scope.AvansSeri = "";
        $scope.AvansSira = 0;
        $scope.TahEvrakTip = 0;
        $scope.Index = 0;
        $scope.PluGrupAdi = "";
        $scope.DivPlu = false;
        $scope.PluGrupIndex = "";
        $scope.PluStokKod = "";
        $scope.IadeSeri = "";
        $scope.IadeSira = "";
        $scope.TxtMiktarGuncelle = 0;
        $scope.TxtFiyatGuncelle = 0;
        $scope.TxtKasaSifre = "";
        $scope.TxtOkcMesaj = "OKC Cihazıyla Eşleşme Yapılıyor.";
        $scope.BtnTxtOkcEslesme = "İptal";

        $scope.Kullanici = UserParam.Kullanici;
        $scope.KasaNo = 1;
        $scope.Saat = moment(new Date(),"HH:mm:ss").format("HH:mm:ss");

        $scope.TahPanelKontrol = false;
        $scope.Klavye = false;

        $scope.TahTip = 0;
        $scope.TxtAraToplamTutar = "";
        $scope.TahKalan = 0;
        $scope.TahParaUstu = 0;

        $scope.IslemListeSelectedIndex = 0;
        $scope.TahIslemListeSelectedIndex = 0;
        $scope.ParkIslemListeSelectedIndex = 0;
        $scope.SonSatisListeSelectedIndex = 0;

        $scope.CmbCariAra = "0";
        $scope.CmbStokAra = "0";
        $scope.TxtCariAra = "";
        $scope.TxtStokAra = "";

        $scope.CariListe = [];
        $scope.StokListe = [];
        $scope.BarkodListe = []; 
        $scope.Stok = [];
        $scope.PluList = [];
        $scope.PluGrpList = [];
        $scope.SatisList = [];        
        $scope.SatisFisList = []; 
        $scope.TahList = [];   
        $scope.ParkList =[];     
        $scope.SonSatisList = [];
        $scope.SonSatisDetayList = [];   
        $scope.SonSatisTahDetayList = [];
        $scope.AraToplamRaporList = [];
        $scope.KasaAraToplamRaporList = [];

        setTimeout(function()
        { 
            db.LCDPrint
            (
                {
                    blink : 0,
                    text :  db.PrintText("A tres bientot",20)
                }
            );
        }, 5000);

        setTimeout(function()
        { 
            db.LCDPrint
            (
                {
                    blink : 0,
                    text :  db.PrintText("Bonjour",20) + 
                            db.PrintText(moment(new Date()).format("DD.MM.YYYY"),20)
                }
            );
        }, 10000);
        
        setInterval(()=>
        {
            db.SafeApply($scope,function()
            {
                $scope.Saat = moment(new Date(),"HH:mm:ss").format("HH:mm:ss");
            })
        },1000);

        setInterval(()=>
        {
            db.SafeApply($scope,function()
            {
                $scope.Tarih = new Date().toLocaleDateString('tr-TR',{ year: 'numeric', month: 'numeric', day: 'numeric' });
            })
        },21600000);

        InitClass();        
    }
    function InitClass()
    {
        $scope.Class = {};
        $scope.Class.BtnFiyatGor = "form-group btn btn-info btn-block my-1";
        $scope.Class.BtnPersonelSatis = "form-group btn btn-warning btn-block my-1";
        $scope.Class.BtnIadeAl = "form-group btn btn-danger btn-block my-1";
        $scope.Class.BtnPluEdit = "form-group btn btn-block btn-success my-1 h-80";
        $scope.Class.BtnEdit = "icon wb-lock"
    }
    function InitCariGrid()
    {
        $("#TblCari").jsGrid
        ({
            width: "100%",
            height: "300px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.CariListe,
            paging : true,
            pageSize: 30,
            pageButtonCount: 5,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields: 
            [
                {
                    name: "CODE",
                    type: "number",
                    align: "center",
                    width: 100
                    
                },
                {
                    name: "NAME",
                    type: "text",
                    align: "center",
                    width: 300
                },
                {
                    name: "ADRESS",
                    type: "text",
                    align: "center",
                    width: 300
                }
            ],
            rowClick: function(args)
            {
                $scope.CariListeRowClick(args.itemIndex,args.item,this);
                $scope.$apply();
            }
        });
    }
    function InitStokGrid()
    {
        $("#TblStok").jsGrid
        ({
            width: "100%",
            height: "300px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.StokListe,
            fields: 
            [
                {
                    name: "CODE",
                    type: "text",
                    align: "center",
                    width: 100
                    
                },
                {
                    name: "NAME",
                    type: "text",
                    align: "center",
                    width: 300
                },
                {
                    name: "PRICE",
                    type: "number",
                    align: "center",
                    width: 100
                }
            ],
            rowClick: function(args)
            {
                $scope.StokListeRowClick(args.itemIndex,args.item,this);
                $scope.$apply();
            }
        });
    }
    function InitBarkodGrid()
    {
        $("#TblBarkod").jsGrid
        ({
            width: "100%",
            height: "300px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.BarkodListe,
            fields: 
            [
                {
                    name: "BARCODE",
                    type: "text",
                    align: "center",
                    width: 100
                    
                },
                {
                    name: "NAME",
                    type: "text",
                    align: "center",
                    width: 300
                }
            ],
            rowClick: function(args)
            {
                $scope.BarkodListeRowClick(args.itemIndex,args.item,this);
                $scope.$apply();
            }
        });
    }
    function InitIslemGrid()
    {   
        $("#TblIslem").jsGrid({
            responsive: true,
            width: "100%",
            height: "215px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.SatisList,
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [
            {
                name: "NO",
                title: "NO",
                type: "text",
                align: "center",
                width: 30
            },
            {
                name: "ITEM_NAME",
                title: "ADI",
                type: "text",
                align: "center",
                width: 200,
                itemTemplate: function(value,item)
                {
                    return "<div style='white-space: nowrap;overflow: hidden;text-overflow: ellipsis;'>" + value + "</div>";
                }
            },
            {
                name: "QUANTITY",
                title: "MIKTAR",
                type: "number",
                align: "center",
                width: 60
            },         
            {
                name: "PRICE",
                title: "FIYAT",
                type: "number",
                align: "center",
                width: 60
            },
            {
                name: "AMOUNT",
                title: "TUTAR",
                type: "number",
                align: "center",
                width: 60
            }],
            rowClick: function(args)
            {                   
                if(args.event.target.cellIndex == 2)
                {
                    $scope.IslemListeSelectedIndex = args.itemIndex;
                    $scope.BtnMiktarGuncelle();
                }
                if(args.event.target.cellIndex == 3 && $scope.Class.BtnIadeAl == "form-group btn btn-primary btn-block my-1")
                {
                    $scope.IslemListeSelectedIndex = args.itemIndex;
                    $scope.BtnFiyatGuncelle();
                }

                $scope.IslemListeRowClick(args.itemIndex,args.item);
                $scope.$apply();                
            }
        });
    }
    function InitTahIslemGrid()
    {   
        $("#TblTahIslem").jsGrid({
            responsive: true,
            width: "100%",
            height: "140px",
            updateOnResize: true,
            heading: false,
            selecting: true,
            data : $scope.TahList,
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [{
                name: "TYPE_NAME",
                title: "TIP",
                type: "number",
                align: "center",
                width: 60
            }, 
            {
                name: "AMOUNT",
                title: "TUTAR",
                type: "number",
                align: "center",
                width: 60
            }],
            rowClick: function(args)
            {
                $scope.TahIslemListeRowClick(args.itemIndex,args.item);
                $scope.$apply();
            }
        });
    }
    function InitParkIslemGrid()
    {   
        $("#TblParkIslem").jsGrid({
            responsive: true,
            width: "100%",
            height: "385px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.ParkList,
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [{
                name: "LUSER",
                title: "KULLANICI",
                type: "text",
                align: "center",
                width: 75
            },
            {
                name: "DATE",
                title: "TARIH",
                type: "number",
                align: "center",
                width: 75
            },
            {
                name: "REF",
                title: "SERI",
                type: "text",
                align: "center",
                width: 50
            }, 
            {
                name: "REF_NO",
                title: "SIRA",
                type: "text",
                align: "center",
                width: 50
            },
            {
                name: "AMOUNT",
                title: "TUTAR",
                type: "number",
                align: "center",
                width: 60
            }],
            rowClick: function(args)
            {
                $scope.ParkIslemListeRowClick(args.itemIndex,args.item);
                $scope.$apply();
            }
        });
    }
    function InitSonSatisGrid()
    {
        $("#TblSonSatis").jsGrid({
            responsive: true,
            width: "100%",
            height: "250px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.SonSatisList,
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [
            {
                name: "CDATE",
                title: "TARIH",
                type: "date",
                align: "center",
                width: 50
            },
            {
                name: "CHOUR",
                title: "SAAT",
                type: "date",
                align: "center",
                width: 50
            },
            {
                name: "REF",
                title: "SERI",
                type: "TEXT",
                align: "center",
                width: 35
            },
            {
                name: "REF_NO",
                title: "SIRA",
                type: "number",
                align: "center",
                width: 35
            },
            {
                name: "LINE_NO",
                title: "SATIR",
                type: "number",
                align: "center",
                width: 50
            },
            {
                name: "USER",
                title: "KULLANICI",
                type: "TEXT",
                align: "center",
                width: 75
            },
            {
                name: "AMOUNT",
                title: "TUTAR",
                type: "number",
                align: "center",
                width: 50
            }
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
            height: "250px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            paging : true,
            pageSize: 5,
            pageButtonCount: 3,
            data : $scope.SonSatisDetayList,
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [
            {
                name: "BARCODE",
                title: "BARKOD",
                type: "number",
                align: "center",
                width: 100
            },
            {
                name: "NAME",
                title: "STOK ADI",
                type: "TEXT",
                align: "center",
                width: 150
            },            
            {
                name: "QUANTITY",
                title: "MIKTAR",
                type: "number",
                align: "center",
                width: 50
            },
            {
                name: "PRICE",
                title: "FIYAT",
                type: "number",
                align: "center",
                width: 50
            },
            {
                name: "AMOUNT",
                title: "TUTAR",
                type: "number",
                align: "center",
                width: 50
            }],
            rowClick: function(args)
            {
                // $scope.SonSatisDetayRowClick(args.itemIndex,args.item);
                // $scope.$apply();
            }
        });
    }
    function InitSonSatisTahDetayGrid()
    {
        $("#TblSonSatisTahDetay").jsGrid({
            width: "100%",
            height: "250px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            editing: true,
            data : $scope.SonSatisTahDetayList,
            paging : true,
            pageSize: 5,
            pageButtonCount: 3,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",            
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [
            {
                name: "TYPE",
                title: "TİP",
                align: "center",
                width: 50
            },
            {
                name: "DOC_TYPE",
                title: "EVRAK TİP",
                align: "center",
                width: 50
            },
            {
                name: "AMOUNT",
                title: "TUTAR",
                type: "decimal",
                align: "center",
                width: 35
            },
            {
                name: "CHANGE",
                title: "PARA USTU",
                align: "center",
                width: 35
            },
            // { type: "control", modeSwitchButton: true, editButton: false,deleteButton:false }
            ],
            onItemUpdated: function(args)
            {
                if(db.SumColumn($scope.SonSatisTahDetayList,"AMOUNT") <= $scope.SonSatisList[$scope.SonSatisListeSelectedIndex].AMOUNT)
                {
                    let TmpQuery = 
                    {
                        db : $scope.Firma,
                        query:  "UPDATE POS_PAYMENT SET AMOUNT = @AMOUNT WHERE GUID = @GUID",
                        param:  ['AMOUNT','GUID'],
                        type:   ['float','string|50'],
                        value:  [args.item.AMOUNT,args.item.GUID]
                    }
                    db.ExecuteQuery(TmpQuery,function(){});
                }
                else
                {
                    db.GetData($scope.Firma,'PosSonSatisTahDetayGetir',[$scope.Sube,$scope.SonSatisList[$scope.SonSatisListeSelectedIndex].REF,$scope.SonSatisList[$scope.SonSatisListeSelectedIndex].REF_NO],function(PosSonSatisTahDetay)
                    {  
                        $scope.SonSatisTahDetayList = PosSonSatisTahDetay;
                        $("#TblSonSatisTahDetay").jsGrid({data : $scope.SonSatisTahDetayList});
                    });
                    alertify.alert("Girilen tutar hatalıdır !")
                }
            }
        });
    }
    function InitAraToplamGrid()
    {
        $("#TblAraToplam").jsGrid({
            responsive: true,
            width: "100%",
            height: "250px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.RprAraToplam,
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [
                {
                    name: "DOC_TYPE",
                    title: "EVRAK TİP",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "DEPARTMENT",
                    title: "ŞUBE",
                    type: "date",
                    align: "center",
                    width: 50
                },
                {
                    name: "CUSER",
                    title: "KULLANICI",
                    type: "TEXT",
                    align: "center",
                    width: 50
                },
                {
                    name: "AMOUNT",
                    title: "TOPLAM",
                    type: "number",
                    align: "center",
                    width: 100
                },
            ],
            rowClick: function(args)
            {
                $scope.$apply();
            }
        });
    }
    function InitKasaAraToplamGrid()
    {
        $("#TblKasaAraToplam").jsGrid({
            responsive: true,
            width: "100%",
            height: "250px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.KasaAraToplamRaporList,
            rowClass: function (item, itemIndex)
            {
                return "rowheight";
            },
            fields: 
            [
                {
                    name: "TYPE",
                    title: "SATIŞ TİP",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "DEPARTMENT",
                    title: "ŞUBE",
                    type: "date",
                    align: "center",
                    width: 50
                },
                {
                    name: "CUSER",
                    title: "KULLANICI",
                    type: "TEXT",
                    align: "center",
                    width: 50
                },
                {
                    name: "AMOUNT",
                    title: "TOPLAM",
                    type: "number",
                    align: "center",
                    width: 100
                },
            ],
            rowClick: function(args)
            {
                $scope.$apply();
            }
        });
    }
    function InsertSonYenile(pData)
    {    
        $scope.SatisList = pData;
        $("#TblIslem").jsGrid({data : $scope.SatisList});    
        $scope.TxtBarkod = "";
        
        DipToplamHesapla();
        //$scope.Yukleniyor =  false  
        $window.document.getElementById("TxtBarkod").focus();
    } 
    function InsertFisYenile(pData)
    {   
        $scope.SatisFisList = pData;
        $scope.FisSeri = pData[0].REF
        $scope.FisSira = pData[0].REF_NO
        $scope.FisTarih = pData[0].CDATE
        $scope.FisSaat = pData[0].CHOUR
        
        DipToplamFisHesapla();
        //$scope.Yukleniyor =  false  
        $window.document.getElementById("TxtBarkod").focus();
    }  
    function DipToplamHesapla()
    {
        $scope.AraToplam = 0;
        $scope.ToplamKdv = 0;
        $scope.GenelToplam = 0;
        $scope.ToplamIskonto = 0;
        $scope.ToplamFisIskonto = 0;

        angular.forEach($scope.SatisList,function(value)
        {
            let TmpKdv = (((value.QUANTITY * value.PRICE) - value.DISCOUNT)) - ((((value.QUANTITY * value.PRICE) - value.DISCOUNT)) / ((value.VAT / 100) + 1)); 
            $scope.ToplamKdv += TmpKdv; 
            $scope.AraToplam += (value.QUANTITY * value.PRICE) - TmpKdv;
            $scope.ToplamIskonto += value.DISCOUNT;
        });

        $scope.ToplamKalan = (($scope.AraToplam - $scope.ToplamIskonto) + $scope.ToplamKdv) - db.SumColumn($scope.TahList,"AMOUNT");
        $scope.GenelToplam = (($scope.AraToplam - $scope.ToplamIskonto) + $scope.ToplamKdv);
    }
    function DipToplamFisHesapla()
    {
        $scope.FisAraToplam = 0;
        $scope.FisToplamKdv = 0;
        $scope.FisGenelToplam = 0;
        $scope.FisToplamIskonto = 0;

        angular.forEach($scope.SatisFisList,function(value)
        {
            $scope.FisAraToplam += value.QUANTITY * value.PRICE;
            $scope.FisToplamKdv += ((value.QUANTITY * value.PRICE) - value.DISCOUNT) * (value.VAT / 100);     
            $scope.FisToplamIskonto += value.DISCOUNT + (value.DISCOUNT * (value.VAT / 100));
        });
        
        $scope.FisGenelToplam = parseFloat($scope.FisAraToplam - $scope.FisToplamIskonto).toFixed(2);
    }
    function TxtBarkodKeyPress()
    {   
        if($scope.TxtBarkod.indexOf("-") != -1)
        {   
            $scope.PosSatisMiktarUpdate($scope.SatisList[$scope.IslemListeSelectedIndex],$scope.TxtBarkod.split("-")[1]);
        }
        else if($scope.TxtBarkod.indexOf("/") != -1)
        {
            $scope.BtnIskonto($scope.TxtBarkod.split("/")[1]);
        }
        // else if($scope.TxtBarkod.indexOf("*") != -1)
        // {
        //     $scope.PosSatisMiktarUpdate($scope.SatisList[$scope.IslemListeSelectedIndex],$scope.TxtBarkod.split("*")[1] * $scope.SatisList[$scope.IslemListeSelectedIndex].QUANTITY);
        // }
        else
        {   
            $scope.StokGetir($scope.TxtBarkod);
        }
    }
    function TahSonYenile()
    {  
        FirstKey = false;      
        $("#TblTahIslem").jsGrid({data : $scope.TahList}); 
        
        if($scope.TahList.length > 0)
        {            
            $scope.TahKalan = parseFloat($scope.GenelToplam).toFixed(2) - db.SumColumn($scope.TahList,"AMOUNT").toFixed(2);
            $scope.TahParaUstu = db.SumColumn($scope.TahList,"CHANGE"); 
            $scope.TahIslemListeRowClick($scope.TahList.length-1,$scope.TahList[$scope.TahList.length-1]); 
        }
        else
        {    
            $scope.TahKalan = parseFloat($scope.GenelToplam).toFixed(2);
            $scope.TahParaUstu = 0; 
        }

        $scope.TxtAraToplamTutar = parseFloat($scope.TahKalan).toFixed(2);
    }  
    function FiyatUpdate(pData)
    {
        return new Promise(async resolve => 
        {
            let TmpMiktar = db.SumColumn($scope.SatisList,"QUANTITY","ITEM_CODE = " + pData.ITEM_CODE);
            let TmpFiyat = pData.PRICE;

            let TmpFiyatData = await db.GetPromiseTag($scope.Firma,'PosSatisFiyatGetir',[pData.ITEM_CODE,TmpMiktar]);
                            
            if(TmpFiyatData.length > 0)
            {
                TmpFiyat = TmpFiyatData[0].PRICE;
            }

            await db.GetPromiseTag($scope.Firma,'PosSatisFiyatUpdate',[TmpFiyat,pData.GUID]);

            resolve();
        });
    } 
    function BirimFiyatUpdate(pFiyat,pData)
    {
        return new Promise(async resolve => 
        {
            await db.GetPromiseTag($scope.Firma,'PosSatisFiyatUpdate',[pFiyat,pData.GUID]);
            resolve();
            db.GetData($scope.Firma,'PosSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(PosSatisData)
            {  
                InsertSonYenile(PosSatisData);
                $scope.IslemListeSelectedIndex = 0;  
                $scope.IslemListeRowClick($scope.IslemListeSelectedIndex,$scope.SatisList[$scope.IslemListeSelectedIndex]);
                $scope.ToplamMiktar = db.SumColumn($scope.SatisList,"QUANTITY")
                $scope.ToplamSatir =  $scope.SatisList.length    
                
                db.GetData($scope.Firma,'PosFisSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(PosSatisFisData)
                {  
                    InsertFisYenile(PosSatisFisData);   
                }); 

                db.LCDPrint
                (
                    {
                        blink : 0,
                        text :  db.PrintText(PosSatisData[PosSatisData.length - 1].ITEM_NAME,11) + " " + 
                                db.PrintText(PosSatisData[PosSatisData.length - 1].PRICE.toString() + "EUR" ,8,"Start") +
                                "TOTAL : " + db.PrintText(db.SumColumn(PosSatisData,"AMOUNT").toString() + "EUR",12,"Start")
                    }                        
                );
            });
        });
    } 
    function SatirBirlestir()
    {
        let TmpStatus = false;
        let TmpIndex = -1;

        for (let i = 0; i < $scope.SatisList.length; i++) 
        {
            if($scope.SatisList[i].ITEM_CODE == $scope.Stok[0].CODE)
            {
                TmpStatus = true;
                TmpIndex = i;
            }
        }

        return {Status : TmpStatus,Index : TmpIndex};
    }
    function SatisKapat()
    {
        if($scope.TahKalan <= 0)
        {
            if(typeof require != 'undefined')
            {
                let TmpData = 
                {
                    SALES : [],
                    PAYMENT : [] 
                }

                for(let i = 0;i < $scope.SatisList.length;i++)
                {
                    let TmpSale = {};
                    TmpSale.NAME = $scope.SatisList[i].ITEM_NAME;
                    TmpSale.QUANTITY = $scope.SatisList[i].QUANTITY;
                    TmpSale.AMOUNT = $scope.SatisList[i].PRICE * 100;
                    TmpSale.TAX = 1;

                    TmpData.SALES.push(TmpSale);
                }

                for(let i = 0;i < $scope.TahList.length;i++)
                {
                    let TmpPayment = {};
                    TmpPayment.TYPE = $scope.TahList[i].TYPE;
                    TmpPayment.AMOUNT = $scope.TahList[i].AMOUNT * 100;

                    TmpData.PAYMENT.push(TmpPayment);
                }
                db.Ingenico.SendData(TmpData);
            } 

            db.ExecuteTag($scope.Firma,'PosSatisKapatUpdate',[$scope.Sube,$scope.Seri,$scope.Sira,$scope.EvrakTip],function(data)
            {   
                let TmpQuery = 
                {
                    db : $scope.Firma,
                    query:  "SELECT " + 
                            "CASE WHEN VAT = 20 THEN 'B' WHEN VAT = 5.5 THEN 'C' END AS VAT_TYPE, " + 
                            "VAT AS VAT, " +  
                            "(SUM(QUANTITY) * SUM(PRICE)) - (((SUM(QUANTITY) * SUM(PRICE)) / 100) * VAT) AS HT, " + 
                            "((SUM(QUANTITY) * SUM(PRICE)) / 100) * VAT AS TVA, " +
                            "ROUND(SUM(QUANTITY) * SUM(PRICE),4) AS TTC, " +
                            "ISNULL((SELECT COUNT(REF) AS TICKET FROM (SELECT REF FROM POS_SALES " + 
                            "WHERE DOC_DATE >= CONVERT(NVARCHAR(10),GETDATE(),112) " + 
                            "AND DOC_DATE <= CONVERT(NVARCHAR(10),GETDATE(),112) " + 
                            "AND DEPARTMENT = @DEPARTMENT " + 
                            "AND STATUS = 1 " + 
                            "GROUP BY REF,REF_NO) AS TMP),1) AS TICKET " + 
                            "FROM POS_SALES AS POS " +
                            "WHERE DEPARTMENT = @DEPARTMENT AND TYPE = @TYPE AND REF = @REF AND REF_NO = @REF_NO " +
                            "GROUP BY VAT",
                    param:  ['DEPARTMENT','TYPE','REF','REF_NO'],
                    type:   ['int','int','string|25','int'],
                    value:  [$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira]
                }
                db.GetDataQuery(TmpQuery,function(pData)
                {
                    //SATIŞ SONUNDA PARA ÜSTÜ MODAL EKRANI AÇILIYOR. TMPPARAUSTU DEĞİŞKENİ EKRAN YENİLENDİĞİ İÇİN KULLANILDI. 
                    //$scope.TmpParaUstu = $scope.TahParaUstu;
                    if($scope.TahParaUstu > 0)
                    {
                        $("#MdlParaUstu").modal("show");                    
                        setTimeout(()=>{$("#MdlParaUstu").modal("hide")},5000);
                    }
                                        
                    // db.EscposPrint($scope.SatisList,$scope.TahList,pData,function()
                    // {
                    //     //EĞER TAHSİLAT İÇERİSİNDE NAKİT VARSA KASAYI AÇ YOKSA KASAYI AÇMA BUNUN İÇİN TAHSİLAT TABLOSUNDAKİ TYPE ALANININ TOPLAM DEĞERİNE BAKIYORUM.
                    //     if(db.SumColumn($scope.TahList,"TYPE") == 0)
                    //     {
                    //         db.EscposCaseOpen();
                    //     }
                    // });
    
                    setTimeout(()=>
                    {
                        $('#MdlAraToplam').modal('hide');
                        $scope.YeniEvrak();
                        $scope.TxtBarkod = "";
                        $scope.TahPanelKontrol = false;
                    },1000)
                    
                });                                  
            });
        }
    }
    document.onkeydown = function(e)
    {
        if(FocusBarkod)
        {
            $window.document.getElementById("TxtBarkod").focus();

            if(e.which == 38)
            {
                if($scope.SatisList.length > 0)
                {
                    $scope.BtnUpClick();
                }
            }
            else if(e.which == 40)
            {
                if($scope.SatisList.length > 0)
                {
                    $scope.BtnDownClick();
                }
            }
        }
        else if(FocusAraToplam)
        {
            $window.document.getElementById("TxtAraToplamTutar").focus();
        }
        else if(FocusMusteri)
        {
            $window.document.getElementById("TxtCariAra").focus();
            if(e.which == 13)
            {
                $scope.BtnCariGridGetir();
            }
        }
        else if(FocusStok)
        {
            $window.document.getElementById("TxtStokAra").focus();
        }
        else if(FocusMiktarGuncelle)
        {
            $window.document.getElementById("TxtMiktarGuncelle").focus();
        }
        else if(FocusKartOdeme)
        {
            $window.document.getElementById("TxtKartOdemeTutar").focus();
        }
        else if(FocusYetkiliSifre)
        {
            $window.document.getElementById("TxtYetkiliSifre").focus();
        }
        else if(FocusAvans)
        {
            $window.document.getElementById("TxtYetkiliSifre").focus();
        }
        else if(FocusFiyatGuncelle)
        {
            $window.document.getElementById("TxtFiyatGuncelle").focus();
        }
        else if(FocusKasaSifre)
        {
            $window.document.getElementById("TxtKasaSifre").focus();
        }
    }
    $scope.IslemListeRowClick = function(pIndex,pItem)
    {
        if ( IslemSelectedRow ) { IslemSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = $("#TblIslem").jsGrid("rowByItem", pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        IslemSelectedRow = $row;
        $scope.IslemListeSelectedIndex = pIndex;
    }
    $scope.TahIslemListeRowClick = function(pIndex,pItem)
    {
        if ( TahIslemSelectedRow ) { TahIslemSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = $("#TblTahIslem").jsGrid("rowByItem", pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        TahIslemSelectedRow = $row;
        $scope.TahIslemListeSelectedIndex = pIndex;
    }
    $scope.ParkIslemListeRowClick = function(pIndex,pItem)
    {
        if ( ParkIslemSelectedRow ) { ParkIslemSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = $("#TblParkIslem").jsGrid("rowByItem", pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        ParkIslemSelectedRow = $row;
        $scope.ParkIslemListeSelectedIndex = pIndex;
    }
    $scope.CariListeRowClick = function(pIndex,pItem,pObj)
    {
        if ( CariSelectedRow ) { CariSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = pObj.rowByItem(pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        CariSelectedRow = $row;
        
        $scope.CariKodu = $scope.CariListe[pIndex].CODE;
        $scope.CariAdi = $scope.CariListe[pIndex].NAME;
    }
    $scope.StokListeRowClick = function(pIndex,pItem,pObj)
    {
        if ( StokSelectedRow ) { StokSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = pObj.rowByItem(pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        StokSelectedRow = $row;

        $scope.TxtBarkod = $scope.StokListe[pIndex].CODE;
    }
    $scope.BarkodListeRowClick = function(pIndex,pItem,pObj)
    {
        if ( BarkodSelectedRow ) { BarkodSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = pObj.rowByItem(pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        BarkodSelectedRow = $row;
        $scope.TxtBarkod = $scope.BarkodListe[pIndex].BARCODE;
        $scope.StokGetir($scope.TxtBarkod);
        $("#MdlBarkodListele").modal("hide");
    }
    $scope.SonSatisRowClick = function(pIndex,pItem,pObj)
    {
        if ( SonSatisSelectedRow ) { SonSatisSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = $("#TblSonSatis").jsGrid("rowByItem", pItem);
        
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        SonSatisSelectedRow = $row;
        $scope.SonSatisListeSelectedIndex = pIndex;

        let SonSatisDetay = pItem;
        
        db.GetData($scope.Firma,'PosSonSatisDetayGetir',[$scope.Sube,SonSatisDetay.REF,SonSatisDetay.REF_NO,$scope.Kullanici],function(PosSonSatisDetay)
        {  
            $scope.SonSatisDetayList = PosSonSatisDetay;
            $("#TblSonSatisDetay").jsGrid({data : $scope.SonSatisDetayList});
        });
        db.GetData($scope.Firma,'PosSonSatisTahDetayGetir',[$scope.Sube,SonSatisDetay.REF,SonSatisDetay.REF_NO,$scope.Kullanici],function(PosSonSatisTahDetay)
        {  
            $scope.SonSatisTahDetayList = PosSonSatisTahDetay;
            $("#TblSonSatisTahDetay").jsGrid({data : $scope.SonSatisTahDetayList});
        });
    }
    $scope.YeniEvrak = async function()
    {
        db.Connection(async function(data)
        {
            db.On("SerialBarcode",function(data)
            {
                $scope.TxtBarkod = data.result.substring(1,data.result.length).toString().trim();
                TxtBarkodKeyPress();
            })

            Init();
            InitIslemGrid();
            InitParkIslemGrid();
            InitTahIslemGrid();
            InitCariGrid();
            InitStokGrid();
            InitBarkodGrid();
            InitSonSatisGrid();
            InitSonSatisDetayGrid();
            InitSonSatisTahDetayGrid();
            InitAraToplamGrid();
            InitKasaAraToplamGrid();

            $scope.Seri = UserParam.PosSatis.Seri;
            $scope.TahSeri = UserParam.PosSatis.TahSeri;
            $scope.AvansSeri = UserParam.PosSatis.AvansSeri;
            $scope.EvrakTip = UserParam.PosSatis.EvrakTip;
            $scope.CariKodu = UserParam.PosSatis.Cari;
            $scope.Sube = UserParam.PosSatis.Sube;
            $scope.Kullanici = UserParam.Kullanici;
            $scope.IadeSeri = UserParam.PosSatis.IadeSeri;
            $scope.Miktar = 1;

            $scope.Stok = 
            [
                {
                    BIRIM : '',
                    BIRIMPNTR : 0, 
                    FIYAT : 0,
                    TUTAR : 0,
                    INDIRIM : 0,
                    KDV : 0,
                    TOPTUTAR :0
                }
            ];

            // CARI GETIR
            if($scope.CariKodu != "")
            {
                db.GetData($scope.Firma,'PosCariGetir',[$scope.CariKodu,''],function(data)
                {
                    if(data.length > 0)
                    {
                        $scope.CariListe = data;
                    
                        $("#TblCari").jsGrid({data : $scope.CariListe});
        
                        let Obj = $("#TblCari").data("JSGrid");
                        let Item = Obj.rowByItem(data[0]);
                        
                        $scope.CariListeRowClick(0,Item,Obj);
                    }
                });
            }
            //PLU GRUP GETİR
            db.GetData($scope.Firma,'PosPluGrupGetir',[$scope.Kullanici,-1,0],function(PluGrpData)
            {
                $scope.PluGrpList = PluGrpData;
                
                if($scope.PluGrpList.length > 0)
                {
                    $scope.PluGrupIndex = PluGrpData[0].GRUP_INDEX
                    db.GetData($scope.Firma,'PosPluGrupGetir',[$scope.Kullanici,$scope.PluGrpList[0].GRUP_INDEX,1],function(PluGrpData)
                    {   
                        $scope.PluList = PluGrpData
                    });
                }
            });
            //PARKTAKİ ISLEMLER
            db.GetData($scope.Firma,'PosSatisParkListe',[$scope.Sube,$scope.EvrakTip,$scope.Kullanici,0],function(ParkData)
            {   
                $scope.ParkList = ParkData;
                $scope.ParkIslemSayisi = $scope.ParkList.length;

                $("#TblParkIslem").jsGrid({data : $scope.ParkList}); 
            });
            
            await db.MaxSira($scope.Firma,'MaxPosSatisSira',[$scope.Sube,$scope.Seri,$scope.EvrakTip],function(data){$scope.Sira = data});
            await db.MaxSira($scope.Firma,'MaxPosTahSira',[$scope.Sube,$scope.TahSeri,0],function(data){$scope.TahSira = data});
            await db.MaxSira($scope.Firma,'MaxPosAvansSira',[$scope.Sube,$scope.AvansSeri],function(data){$scope.AvansSira = data;});
            await db.MaxSira($scope.Firma,'MaxPosIadeSira',[$scope.Sube,$scope.IadeSeri,1],function(data){$scope.IadeSira = data;});
        });
    }
    $scope.BtnCariGridGetir = function()
    {
        db.GetData($scope.Firma,'PosCariListeGetir',[$scope.TxtCariAra],function(data)
        {
            $scope.CariListe = data;   
            $("#TblCari").jsGrid({data : $scope.CariListe});
        });
    }
    $scope.BtnCariGridSec = function()
    {   
        $("#MdlMusteriListele").modal('hide');
        $scope.TxtCariAra = "";
        if($scope.SatisList.length > 0)
        {   
            //CARİ UPDATE
            var TmpQuery = 
            {
                db : '{M}.' + $scope.Firma,
                query:  "UPDATE POS_SALES SET CUSTOMER_CODE = @CUSTOMER_CODE WHERE REF = @REF AND REF_NO = @REF_NO AND DEPARTMENT = @DEPARTMENT",
                param:  ['CUSTOMER_CODE','REF','REF_NO','DEPARTMENT'],
                type:   ['string|25','string|25','int','int'],
                value:  [$scope.CariKodu,$scope.Seri,$scope.Sira,$scope.Sube]
            }
            db.ExecuteQuery(TmpQuery,function(UpdateResult)
            {
                
            });
        }

        if($scope.CariKodu != UserParam.PosSatis.Cari && $scope.SatisList.length > 0)
        {
            if($scope.TxtAraToplamTutar.length > 0)
            {   
                $('#MdlMusteriListele').modal('hide');
                //$scope.BtnAraToplam();
            }
        }
    }
    $scope.BtnStokGridGetir = function()
    {
        let Kodu = '';
        let Adi = '';

        if($scope.CmbStokAra == "0")
        {
            Adi = $scope.TxtStokAra + "%";
        }
        else
        {
            Kodu = $scope.TxtStokAra + "%";
        }
        db.GetData($scope.Firma,'StokGetir',[Kodu,Adi],function(StokData)
        {
            $scope.StokListe = StokData;
            $("#TblStok").jsGrid({data : $scope.StokListe});
        });

    }
    $scope.BtnStokGridSec = function()
    {
        $scope.StokGetir($scope.TxtBarkod);
        $("#MdlStokListele").modal('hide');
    }
    $scope.StokGetir = function(pBarkod)
    {
        if(pBarkod != '')
        {   
            $scope.Miktar = 1;

            if(pBarkod.indexOf("*") != -1)
            {
                $scope.Miktar = pBarkod.split("*")[0];
                pBarkod = pBarkod.split("*")[1];
            }

            if(pBarkod.length >= 16)
            {
                let TmpTicket = pBarkod.substring(11,16)
                let TmpYear = pBarkod.substring(pBarkod.length - 1, pBarkod.length);
                
                if(moment(new Date()).format("M") > 1 && moment(new Date()).format("Y").toString().substring(3,4) != TmpYear)
                {
                    alertify.alert("Geçersiz ticket.");
                    $scope.TxtBarkod = "";
                    return;
                }
                
                db.GetData($scope.Firma,'TicketControl',[pBarkod],function(data)
                {
                    if(data.length <= 0)
                    {
                        $scope.TahTip = 3;
                        $scope.TxtAraToplamTutar = parseFloat(TmpTicket / 100).toFixed(2);

                        db.ExecuteTag($scope.Firma,'TicketInsert',[UserParam.Kullanici,UserParam.Kullanici,pBarkod],function(InsertResult)
                        {
                            $scope.PosTahInsert(function()
                            {   
                                DipToplamHesapla();
                                $scope.TahTip = 0;
                            });
                        })
                    }
                    else
                    {
                        alertify.alert("Bu Ticket Daha Önce Okutulmuş!. ");
                    }

                });

                $scope.TxtBarkod = "";
                return;
            }

            let TmpFiyat = 0;

            if(pBarkod.length >= 12 && pBarkod.length <= 14 && (pBarkod.substring(0,2) == "20" || pBarkod.substring(0,2) == "02"))
            {
                TmpFiyat = parseFloat((parseFloat(pBarkod.substring(6,pBarkod.length)) / 1000) * 0.1524).toFixed(2);
                pBarkod = pBarkod.substring(0,6) + "MMMCCF";
            }

            db.StokBarkodGetir($scope.Firma,pBarkod,function(BarkodData)
            {
                if(BarkodData.length > 0)
                { 
                    if(BarkodData[0].PRICE == 0)
                    {
                        alertify.alert("Ürünün fiyat bilgisi tanımsız !");
                        $scope.TxtBarkod = "";
                        return;
                    }

                    $scope.Stok = BarkodData;
                    if(TmpFiyat > 0 )
                    {
                        $scope.Stok[0].PRICE = TmpFiyat;
                    }
                    
                    //EĞER BİLGİ BUTONUNA BASILDIYSA FİYAT GÖR EKRANI ÇIKACAK.
                    if($scope.Class.BtnFiyatGor == "form-group btn btn-warning btn-block my-1")
                    {
                        $scope.TxtBarkod = ""; 
                        $scope.Class.BtnFiyatGor = "form-group btn btn-info btn-block my-1"
                        $('#MdlFiyatGor').modal('show');
                        return;
                    }
                    //BARKOD OKUTULDUKDAN SONRA INSERT İŞLEMİ
                    let TmpSatirBirlestir = SatirBirlestir();
                    if(TmpSatirBirlestir.Status)
                    {
                        $scope.PosSatisMiktarUpdate($scope.SatisList[TmpSatirBirlestir.Index],$scope.SatisList[TmpSatirBirlestir.Index].QUANTITY + ($scope.Miktar * $scope.Stok[0].FACTOR))
                    }
                    else
                    {
                        $scope.PosSatisInsert();
                    }
                }
                else   
                {
                    alertify.alert("Okuttuğunuz Barkod Sistemde Bulunamadı.");
                    $scope.TxtBarkod = "";
                }
            });
        } 
    }
    $scope.PosSatisInsert = function()
    {    
        var InsertData = 
        [
            UserParam.Kullanici,
            UserParam.Kullanici,
            $scope.Sube,
            $scope.EvrakTip,
            $scope.Tarih,
            $scope.Seri,
            $scope.Sira,
            $scope.CariKodu,
            $scope.Stok[0].CODE,
            $scope.Stok[0].BARCODE,
            $scope.Miktar * $scope.Stok[0].FACTOR,
            $scope.Stok[0].UNIT,
            $scope.Stok[0].PRICE = parseFloat($scope.Stok[0].PRICE).toFixed(2),
            0, //ISKONTO TUTAR 1
            $scope.Stok[0].VAT,
            0  //DURUM
        ];
        
        db.ExecuteTag($scope.Firma,'PosSatisInsert',InsertData,async function(InsertResult)
        {               
            if(typeof(InsertResult.result.err) == 'undefined')
            {   
                //*********** BİRDEN FAZLA MİKTARLI FİYAT GÜNCELLEME İÇİN YAPILDI. */
                let TmpSatisData = await db.GetPromiseTag($scope.Firma,'PosSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira]);
                $scope.SatisList = TmpSatisData;

                for (let i = 0; i < $scope.SatisList.length; i++) 
                {               
                    await FiyatUpdate($scope.SatisList[i]);
                }  
                /***************************************************************** */
                db.GetData($scope.Firma,'PosSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(PosSatisData)
                {   
                    db.LCDPrint
                    (
                        {
                            blink : 0,
                            text :  db.PrintText(PosSatisData[PosSatisData.length - 1].ITEM_NAME,11) + " " + 
                                    db.PrintText(PosSatisData[PosSatisData.length - 1].PRICE.toString() + "EUR" ,8,"Start") +
                                    "TOTAL : " + db.PrintText(db.SumColumn(PosSatisData,"AMOUNT").toString() + "EUR",12,"Start")
                        }                        
                    );

                    InsertSonYenile(PosSatisData);      
                    $scope.TxtBarkod = ""; 
                    $scope.IslemListeRowClick(0,$scope.SatisList[0]);
                    $scope.ToplamMiktar = db.SumColumn($scope.SatisList,"QUANTITY"); 
                    $scope.ToplamSatir =  $scope.SatisList.length  
                });
            }
            else
            {
                console.log(InsertResult.result.err);
            }
        });
        db.GetData($scope.Firma,'PosFisSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(PosFisData)
        {   
            InsertFisYenile(PosFisData);   
        });
    }
    $scope.PosTahInsert = function(pCallBack)
    {   
        let TahTutar = 0
        let TahParaUstu = 0;
      
        $scope.TahSeri = $scope.Seri;
        $scope.TahSira = $scope.Sira;

        if(parseFloat($scope.TxtAraToplamTutar.replace(',','.')) <= 0 || parseFloat($scope.TahKalan) <= 0)
        {
            if(typeof(pCallBack) != 'undefined')
            {
                pCallBack();
            }
            return;
        }
        TahTutar = parseFloat($scope.TxtAraToplamTutar.replace(',','.'));
        if($scope.GenelToplam < (db.SumColumn($scope.TahList,"AMOUNT") + parseFloat($scope.TxtAraToplamTutar.replace(',','.'))))
        {
            TahParaUstu = parseFloat((db.SumColumn($scope.TahList,"AMOUNT") + parseFloat($scope.TxtAraToplamTutar.replace(',','.'))) - $scope.GenelToplam).toFixed(2);
            TahTutar = parseFloat(parseFloat($scope.TxtAraToplamTutar.replace(',','.')) - TahParaUstu).toFixed(2);
        }

        var InsertData = 
        [
            UserParam.Kullanici,
            UserParam.Kullanici,
            $scope.Sube,
            $scope.TahTip,
            $scope.EvrakTip, //EVRAKTIP
            $scope.Tarih,
            $scope.TahSeri,
            $scope.TahSira,
            $scope.CariKodu,
            $scope.Kasa,
            TahTutar,
            TahParaUstu,
            1
        ];
        if($scope.TxtAraToplamTutar.replace(',','.') > 0)
        {
            db.ExecuteTag($scope.Firma,'PosTahInsert',InsertData,function(InsertResult)
            {   
                if(typeof(InsertResult.result.err) == 'undefined')
                {                
                    db.GetData($scope.Firma,'PosTahGetir',[$scope.Sube,$scope.EvrakTip,$scope.TahSeri,$scope.TahSira],function(PosTahData)
                    {   
                        $scope.TahList = PosTahData;
                        TahSonYenile();                                                                          
                        SatisKapat();                   
                        $scope.TahPanelKontrol = false;
                    });
                }
                else
                {
                    if(typeof(pCallBack) != 'undefined')
                    {
                        pCallBack();
                    }
                }
            });
        }
    
        localStorage.KasaKodu = $scope.Kasa
    }
    $scope.PosSatisMiktarUpdate = function(pData,pMiktar)
    {   
        pData.QUANTITY = pMiktar;

        db.GetData($scope.Firma,'PosSatisMiktarUpdate',[pMiktar,pData.GUID],async function(data)
        {    
            //*********** BİRDEN FAZLA MİKTARLI FİYAT GÜNCELLEME İÇİN YAPILDI. */      
            for (let i = 0; i < $scope.SatisList.length; i++) 
            {               
                await FiyatUpdate($scope.SatisList[i]);
            }
            //**************************************************************** */
            db.GetData($scope.Firma,'PosSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(PosSatisData)
            {  
                InsertSonYenile(PosSatisData);
                $scope.IslemListeSelectedIndex = 0;  
                $scope.IslemListeRowClick($scope.IslemListeSelectedIndex,$scope.SatisList[$scope.IslemListeSelectedIndex]);
                $scope.ToplamMiktar = db.SumColumn($scope.SatisList,"QUANTITY")
                $scope.ToplamSatir =  $scope.SatisList.length    
                
                db.GetData($scope.Firma,'PosFisSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(PosSatisFisData)
                {  
                    InsertFisYenile(PosSatisFisData);   
                }); 

                db.LCDPrint
                (
                    {
                        blink : 0,
                        text :  db.PrintText(PosSatisData[PosSatisData.length - 1].ITEM_NAME,11) + " " + 
                                db.PrintText(PosSatisData[PosSatisData.length - 1].PRICE.toString() + "EUR" ,8,"Start") +
                                "TOTAL : " + db.PrintText(db.SumColumn(PosSatisData,"AMOUNT").toString() + "EUR",12,"Start")
                    }                        
                );
            });          
        });
    }
    $scope.TxtBarkodPress = function(keyEvent)
    {    
        if($scope.TxtBarkod != "")
        {
            if(keyEvent.which === 13)
            {   
                TxtBarkodKeyPress();
            }
        }
    }
    $scope.TxtTahTutarPress = function(keyEvent)
    {
        if(keyEvent.which === 13)
        {
            $scope.PosTahInsert();   
        }
    }
    $scope.TxtMiktarGuncellePress = function(keyEvent)
    {
        if($scope.TxtMiktarGuncelle != "" && $scope.TxtMiktarGuncelle > 0)
        {
            if(typeof keyEvent == 'undefined')
            {
                $scope.PosSatisMiktarUpdate($scope.SatisList[$scope.IslemListeSelectedIndex],$scope.TxtMiktarGuncelle);
                $("#MdlMiktarGuncelle").modal("hide");
            }
            else
            {
                if(keyEvent.which === 13)
                {
                    $scope.PosSatisMiktarUpdate($scope.SatisList[$scope.IslemListeSelectedIndex],$scope.TxtMiktarGuncelle);
                    $("#MdlMiktarGuncelle").modal("hide");
                }
            }
        } 
    }
    $scope.TxtFiyatGuncellePress = async function(keyEvent)
    {
        if($scope.TxtFiyatGuncelle != "" && $scope.TxtFiyatGuncelle > 0)
        {
            if(typeof keyEvent == 'undefined')
            {
                await BirimFiyatUpdate($scope.TxtFiyatGuncelle,$scope.SatisList[$scope.IslemListeSelectedIndex]);
                $("#MdlFiyatGuncelle").modal("hide");
            }
            else
            {
                if(keyEvent.which === 13)
                {
                    await BirimFiyatUpdate($scope.TxtFiyatGuncelle,$scope.SatisList[$scope.IslemListeSelectedIndex]);
                    $("#MdlFiyatGuncelle").modal("hide");
                }
            }
        } 
    }
    $scope.BtnSilClick = function()
    {   
        if(FocusBarkod)
        {
            $scope.TxtBarkod = $scope.TxtBarkod.substring(0,$scope.TxtBarkod.length-1);
        }
        else if(FocusAraToplam)
        {
            $scope.TxtAraToplamTutar = $scope.TxtAraToplamTutar.substring(0,$scope.TxtAraToplamTutar.length-1);
        }
        else if(FocusMusteri)
        {
            $scope.TxtCariAra = $scope.TxtCariAra.substring(0,$scope.TxtCariAra.length-1);
        }
        else if(FocusStok)
        {
            $scope.TxtStokAra = $scope.TxtStokAra.substring(0,$scope.TxtStokAra.length-1);
        }
        else if(FocusMiktarGuncelle)
        {
            $scope.TxtMiktarGuncelle = $scope.TxtMiktarGuncelle.substring(0,$scope.TxtMiktarGuncelle.length-1); 
        }
        else if(FocusKartOdeme)
        {
            $scope.TxtAraToplamTutar = $scope.TxtAraToplamTutar.substring(0,$scope.TxtAraToplamTutar.length-1);
        }
        else if(FocusYetkiliSifre)
        {
            $scope.TxtYetkiliSifre = $scope.TxtYetkiliSifre.substring(0,$scope.TxtYetkiliSifre.length-1);
        }
        else if(FocusKasaSifre)
        {
            $scope.TxtKasaSifre = $scope.TxtKasaSifre.substring(0,$scope.TxtKasaSifre.length-1);
        }
        else if(FocusAvans)
        {
            $scope.TxtAvans = $scope.TxtAvans.substring(0,$scope.TxtAvans.length-1);
        }
    }
    $scope.BtnOnayClick = function()
    {
        TxtBarkodKeyPress();
        $scope.TxtBarkod = "";
    }
    $scope.BtnTusClick = function(Key)
    {  
        if(FocusBarkod)
        {   
            $scope.TxtBarkod = $scope.TxtBarkod + Key; 
        }
        else if(FocusAraToplam)
        {
            if(FirstKey)
            {
                $scope.TxtAraToplamTutar = $scope.TxtAraToplamTutar + Key; 
            }
            else
            {
                $scope.TxtAraToplamTutar = Key; 
                FirstKey = true;
            }
        }
        else if(FocusMusteri)
        {
            $scope.TxtCariAra = $scope.TxtCariAra + Key; 
        }
        else if(FocusStok)
        {
            $scope.TxtStokAra = $scope.TxtStokAra + Key; 
        }
        else if(FocusMiktarGuncelle)
        {
            if(FirstKey)
            {
                $scope.TxtMiktarGuncelle = $scope.TxtMiktarGuncelle + Key; 
            }
            else
            {
                $scope.TxtMiktarGuncelle = Key; 
                FirstKey = true;
            }
        }
        else if(FocusKartOdeme)
        {
            if(FirstKey)
            {
                $scope.TxtAraToplamTutar = $scope.TxtAraToplamTutar + Key; 
            }
            else
            {
                $scope.TxtAraToplamTutar = Key; 
                FirstKey = true;
            }
        }
        else if(FocusYetkiliSifre)
        {
            if(FirstKey)
            {
                $scope.TxtYetkiliSifre = $scope.TxtYetkiliSifre + Key; 
            }
            else
            {
                $scope.TxtYetkiliSifre = Key; 
                FirstKey = true;
            }
        }
        else if(FocusKasaSifre)
        {
            if(FirstKey)
            {
                $scope.TxtKasaSifre = $scope.TxtKasaSifre + Key; 
            }
            else
            {
                $scope.TxtKasaSifre = Key; 
                FirstKey = true;
            }
        }
        else if(FocusAvans)
        {
            if(FirstKey)
            {
                $scope.TxtAvans = $scope.TxtAvans + Key; 
            }
            else
            {
                $scope.TxtAvans = Key; 
                FirstKey = true;
            }
        }
        else if(FocusFiyatGuncelle)
        {
            if(FirstKey)
            {
                $scope.TxtFiyatGuncelle = $scope.TxtFiyatGuncelle + Key; 
            }
            else
            {
                $scope.TxtFiyatGuncelle = Key; 
                FirstKey = true;
            }
        }
    }
    $scope.TxtSeriSira = function(Data)
    {
        $scope.SeriSira = Data;
    }
    $scope.BtnUpClick = function()
    {
        if($scope.SatisList.length > 0)
        {
            if($scope.IslemListeSelectedIndex == 0)
                $scope.IslemListeSelectedIndex = 0;
            else
                $scope.IslemListeSelectedIndex -= 1;

            $scope.IslemListeRowClick($scope.IslemListeSelectedIndex,$scope.SatisList[$scope.IslemListeSelectedIndex]);

            $("#TblIslem").find( ".jsgrid-grid-body").scrollTop(IslemSelectedRow.position().top)
        }
    }
    $scope.BtnDownClick = function()
    {
        if($scope.SatisList.length > 0)
        {
            if($scope.SatisList.length - 1 <= $scope.IslemListeSelectedIndex)
            $scope.IslemListeSelectedIndex = $scope.SatisList.length - 1;
            else
                $scope.IslemListeSelectedIndex += 1;

            $scope.IslemListeRowClick($scope.IslemListeSelectedIndex,$scope.SatisList[$scope.IslemListeSelectedIndex]);
            $("#TblIslem").find( ".jsgrid-grid-body").scrollTop(IslemSelectedRow.position().top)
        }
    }
    $scope.BtnBelgeIptal = function()
    {
        alertify.okBtn('Evet');
        alertify.cancelBtn('Hayır');

        alertify.confirm('Evrağı iptal etmek istediğinize eminmisiniz ?', 
        function()
        { 
            if($scope.SatisList.length > 0)
            {
                db.ExecuteTag($scope.Firma,'PosSatisBelgeIptal',[$scope.Seri,$scope.Sira,$scope.EvrakTip],function(data)
                {
                    if(typeof(data.result.err) == 'undefined')
                    {
                        db.ExecuteTag($scope.Firma,'PosTahIptal',[$scope.Seri,$scope.Sira,0],function(data)
                        {
                            if(typeof(data.result.err) != 'undefined')
                            {
                                console.log(data.result.err);
                            }
                        });

                        $scope.YeniEvrak();
                    }
                    else
                    {
                        console.log(data.result.err);
                    }
                });
            }
            else
            {
                alertify.okBtn("Tamam");
                alertify.alert("Kayıtlı evrak olmadan evrak'ı iptal edemezsiniz !");
            }
        }
        ,function(){});
    }
    $scope.BtnSatirIptal = function()
    {
        alertify.okBtn('Evet');
        alertify.cancelBtn('Hayır');

        alertify.confirm('Satırı iptal etmek istediğinize eminmisiniz ?', 
        function()
        {   
            if($scope.IslemListeSelectedIndex > -1)
            {
                db.ExecuteTag($scope.Firma,'PosSatisSatirIptal',[$scope.SatisList[$scope.IslemListeSelectedIndex].GUID],async function(data)
                {
                    if(typeof(data.result.err) == 'undefined')
                    {
                        if($scope.SatisList.length <= 1)
                        {
                            db.ExecuteTag($scope.Firma,'PosTahIptal',[$scope.Seri,$scope.Sira,0],function(data)
                            {
                                if(typeof(data.result.err) != 'undefined')
                                {
                                    console.log(data.result.err);
                                }
                            });
                            
                            $scope.YeniEvrak();
                        }
                        else
                        {
                            //*********** BİRDEN FAZLA MİKTARLI FİYAT GÜNCELLEME İÇİN YAPILDI. */
                            let TmpSatisData = await db.GetPromiseTag($scope.Firma,'PosSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira]);
                            $scope.SatisList = TmpSatisData;

                            for (let i = 0; i < $scope.SatisList.length; i++) 
                            {               
                                await FiyatUpdate($scope.SatisList[i]);
                            }  
                            /***************************************************************** */
                            db.GetData($scope.Firma,'PosSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(data)
                            {
                                $scope.SatisList = data;
                                $("#TblIslem").jsGrid({data : $scope.SatisList});                                    
                                DipToplamHesapla();
                                $scope.TxtBarkod = ""; 
                                $scope.IslemListeRowClick($scope.SatisList.length-1,$scope.SatisList[$scope.SatisList.length-1]);   
                            });
                        }
                    }
                    else
                    {
                        console.log(data.result.err);
                    }                                        
                });
            }
            else
            {
                alertify.okBtn("Tamam");
                alertify.alert("Seçili satır olmadan evrak iptal edemezsiniz !");
            }
        },
        function(){});
    }
    $scope.BtnParkdakiIslem = function()
    {
        $('#MdlParkIslemler').modal('show');
    }
    $scope.BtnParkaAl = function()
    {
        $scope.YeniEvrak();
    }
    $scope.BtnParkSec = function()
    {
        $scope.Seri = $scope.ParkList[$scope.ParkIslemListeSelectedIndex].REF;
        $scope.Sira = $scope.ParkList[$scope.ParkIslemListeSelectedIndex].REF_NO;

        db.GetData($scope.Firma,'PosSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(PosSatisData)
        {   
            db.GetData($scope.Firma,'PosCariGetir',[PosSatisData[0].CUSTOMER_CODE,''],function(data)
            {
                $scope.CariAdi = data[0].NAME;
                $scope.CariKodu = data[0].CODE;
            });

            InsertSonYenile(PosSatisData);
            $scope.TxtBarkod = ""; 
            $scope.IslemListeRowClick($scope.SatisList.length-1,$scope.SatisList[$scope.SatisList.length-1]);                  

            $('#MdlParkIslemler').modal('hide');

            db.GetData($scope.Firma,'PosTahGetir',[$scope.Sube,0,$scope.Seri,$scope.Sira],function(PosTahData)
            {
                $scope.TahList = PosTahData;
                TahSonYenile(); 
            });

            $scope.ToplamMiktar = db.SumColumn($scope.SatisList,"QUANTITY");
            $scope.ToplamSatir =  $scope.SatisList.length
        });
    }
    $scope.BtnAraToplam = function()
    {   
        if(($scope.Class.BtnIadeAl == "form-group btn btn-primary btn-block my-1") == false)
        {
            if($scope.SatisList.length < 1)
            {
                alertify.okBtn("Tamam");
                alertify.alert("Satış işlemi yapmadan tahsilat giremezsiniz !");
                return;
            }
            
            $("#MdlAraToplam").modal("show");
            FocusAraToplam = true;
            FocusBarkod = false;
            FocusMusteri = false;
            FocusStok = false;
            FocusKartOdeme = false;

            FirstKey = false;

            //EKRANA GİRDİĞİNDE OTOMATİK NAKİT SEÇİLİ GELSİN
            if($scope.TahTip != 2)
            {
                TahTip = 0;
                angular.element('#ChkNakit').trigger('click');
            }
            TahSonYenile();
        }
        else
        {
            alertify.alert("İade Butonu Aktif İşlem Yapılamaz.")
        }
    }
    $scope.BtnMusteriListesi = function()
    {
        $("#MdlMusteriListele").modal("show");
        FocusAraToplam = false;
        FocusBarkod = false;
        FocusMusteri = true;
        FocusStok = false;
        FocusKartOdeme = false;
    }
    $scope.BtnStokListesi = function()
    {
        $("#MdlStokListele").modal("show");
        FocusAraToplam = false;
        FocusBarkod = false;
        FocusMusteri = false;
        FocusStok = true;
        FocusKartOdeme = false;

        setTimeout(function()
        {
            document.getElementById('TxtStokAra').focus()
            document.getElementById('TxtStokAra').setSelectionRange(0, document.getElementById('TxtStokAra').value.length)
        },500);
    }
    $scope.BtnBarkodListesi = function()
    {
        if($scope.TxtBarkod != '')
        {
            let TmpQuery = 
            {
                db : $scope.Firma,
                query:  "SELECT [BARCODE] AS BARCODE,ISNULL((SELECT NAME FROM ITEMS WHERE CODE = [ITEM_CODE]),'') NAME FROM [dbo].[ITEM_BARCODE] WHERE BARCODE LIKE '%' + @BARCODE",
                param : ["BARCODE:string|50"],
                value : [$scope.TxtBarkod]
            }
            db.GetDataQuery(TmpQuery,function(Data)
            {
                $scope.BarkodListe = Data;
                if(Data.length == 1)
                {
                    $scope.TxtBarkod = $scope.BarkodListe[0].BARCODE;
                    $scope.StokGetir($scope.TxtBarkod);
                }
                else if(Data.length > 1)
                {
                    $("#TblBarkod").jsGrid({data : $scope.BarkodListe});
                    $("#MdlBarkodListele").modal("show");
                }
            });
        }
    }
    $scope.BtnTahSatirIptal = function()
    {
        if($scope.TahIslemListeSelectedIndex > -1)
        {
            db.ExecuteTag($scope.Firma,'PosTahSatirIptal',[$scope.TahList[$scope.TahIslemListeSelectedIndex].GUID],function(data)
            {
                if(typeof(data.result.err) == 'undefined')
                {
                    db.GetData($scope.Firma,'PosTahGetir',[$scope.Sube,0,$scope.TahSeri,$scope.TahSira],function(data)
                    {
                        $scope.TahList = data;
                        TahSonYenile();
                    });
                 
                }
                else
                {
                    console.log(data.result.err);
                }                                        
            });
        }
    }
    $scope.BtnTahBelgeIptal = function()
    {   
        if($scope.SatisList.length > 0)
        {
            db.ExecuteTag($scope.Firma,'PosTahIptal',[$scope.TahSeri,$scope.TahSira,0],function(data)
            {
                if(typeof(data.result.err) == 'undefined')
                {
                    $scope.TahList = [];
                    TahSonYenile();
                    $("#MdlAraToplam").modal('hide');
                }
                else
                {
                    console.log(data.result.err);
                }
            });
        }
    }
    $scope.BtnKullaniciDegistir = function()
    {   
        alertify.confirm("Kullanıcı değiştirmek istediğinize eminmisiniz ?",

        function(){
            alertify.okBtn('Evet');
            var url = "index.html";
            $window.location.href = url;
        },
        function(){
            alertify.cancelBtn('Vazgeç');
        });
    }
    $scope.BtnSonSatis = function()
    {   
        $("#TbSonSatisListesi").addClass('active');
        $("#TbMain").removeClass('active');

        db.GetData($scope.Firma,'PosSonSatisGetir',[$scope.Sube,$scope.Tarih,$scope.Kullanici],function(PosSonSatis)
        {  
            $scope.SonSatisList = PosSonSatis;
            $("#TblSonSatis").jsGrid({data : $scope.SonSatisList});
            $scope.TxtBarkod = "";
        });
    }
    $scope.BtnIskonto = function(pIskonto)
    {   
        let tutar = $scope.SatisList[$scope.IslemListeSelectedIndex].PRICE * $scope.SatisList[$scope.IslemListeSelectedIndex].QUANTITY;
        let hesapla = tutar * (pIskonto.replace(',','.') / 100);

        if($scope.GenelToplam < hesapla)
        {   
            alertify.alert("Genel Toplamdan Fazla İskonto Yapılamaz.!");
            $scope.TxtBarkod = "";
        }
        else
        {
            db.ExecuteTag($scope.Firma,'PosSatisIskonto',[hesapla,$scope.SatisList[$scope.IslemListeSelectedIndex].GUID],function(pData)
            {   
                db.GetData($scope.Firma,'PosSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(PosSatisData)
                {   
                    db.GetData($scope.Firma,'PosFisSatisGetir',[$scope.Sube,$scope.EvrakTip,$scope.Seri,$scope.Sira],function(PosSatisFisData)
                    {  
                        InsertFisYenile(PosSatisFisData);   
                    }); 
                    InsertSonYenile(PosSatisData);      
                    $scope.IslemListeRowClick($scope.IslemListeSelectedIndex,$scope.SatisList[$scope.IslemListeSelectedIndex]);  
                    $scope.ToplamMiktar = db.SumColumn($scope.SatisList,"QUANTITY")
                    $scope.ToplamSatir =  $scope.SatisList.length
                });
            });
        }
    }
    $scope.StokListeleEvent = function(keyEvent)
    {
        if(keyEvent.which === 13)
        {
            $scope.BtnStokGridGetir()
        }
    }
    $scope.BtnTahTip = function(pTip)
    {   
        $scope.TahTip = pTip;
  
        if($scope.TahTip == 0)
        {
            $scope.Kasa = UserParam.PosSatis.NakitKasaKodu;
            $scope.KasaSecim = false;
        }
    }
    $scope.BtnKlavye = function()
    {
        $scope.Klavye = true;
    }
    $scope.BtnCikti = function(pTip)
    {
        $scope.CiktiTip = pTip;
    }
    $scope.BtnMiktarGuncelle = function()
    {
        $("#MdlMiktarGuncelle").modal("show");
        $scope.TxtMiktarGuncelle = $scope.SatisList[$scope.IslemListeSelectedIndex].QUANTITY.toString();

        FocusMiktarGuncelle = true;
        FocusAraToplam = false;
        FocusBarkod = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusKartOdeme = false;

        FirstKey = false;
    }
    $scope.BtnFiyatGuncelle = function()
    {
        $("#MdlFiyatGuncelle").modal("show");
        $scope.TxtFiyatGuncelle = $scope.SatisList[$scope.IslemListeSelectedIndex].PRICE.toString();

        FocusFiyatGuncelle = true;
        FocusMiktarGuncelle = false;
        FocusAraToplam = false;
        FocusBarkod = false;
        FocusMusteri = false;
        FocusStok = false;
        FocusKartOdeme = false;

        FirstKey = false;
    }
    $scope.BtnKasaAc = function()
    {
        db.EscposCaseOpen();
    }
    $scope.BtnKartOdeme = function()
    {   
        if(($scope.Class.BtnIadeAl == "form-group btn btn-primary btn-block my-1") == false)
        {           
            if($scope.SatisList.length < 1)
            {
                alertify.okBtn("Tamam");
                alertify.alert("Satış işlemi yapmadan tahsilat giremezsiniz !");
                return;
            }

            $("#MdlKartOdeme").modal("show");

            FocusBarkod = false;
            FocusAraToplam = false;
            FocusMusteri = false;
            FocusStok = false;
            FocusYetkiliSifre = false;
            FocusKartOdeme = true;

            FirstKey = false;

            TahSonYenile();
        }
        else
        {
            alertify.alert("İade Butonu Aktif İşlem Yapılamaz.")
        }
    }
    $scope.BtnKartOdemeGonder = function()
    {
        $scope.TahTip = 1;

        $("#MdlKartOdeme").modal("hide");
        $("#MdlKartYukleniyor").modal("show");        

        db.PaymentSend($scope.TxtAraToplamTutar);        
    }    
    $scope.BtnKartVazgec = function()
    {
        $("#MdlKartYukleniyor").modal("hide");
    } 
    $scope.BtnKartZorla = function()
    {
        $scope.TahTip = 1;

        $("#MdlKartYukleniyor").modal("hide");
        $scope.PosTahInsert(0);
    }   
    $scope.BtnTahOnay = function()
    {
        if($scope.TahTip == 0)
        {
            $scope.PosTahInsert();
        }
        else if($scope.TahTip == 1)
        {
            $('#MdlAraToplam').modal('hide');
            $scope.BtnKartOdemeGonder();
        }
    }
    $scope.BtnPara = function(pTutar)
    {
        if($scope.TahTip == 0)
        {
            $scope.TxtAraToplamTutar = pTutar;
            $scope.PosTahInsert(3);
        }
    }
    $scope.BtnArti = function()
    {
        $scope.PosSatisMiktarUpdate($scope.SatisList[$scope.IslemListeSelectedIndex],$scope.SatisList[$scope.IslemListeSelectedIndex].QUANTITY + 1);
    } 
    $scope.BtnEksi = function()
    {
        if($scope.SatisList[$scope.IslemListeSelectedIndex].QUANTITY == 1)
        {
            alertify.alert("Miktar 1 den küçük olamaz.")
            return;
        }
        $scope.PosSatisMiktarUpdate($scope.SatisList[$scope.IslemListeSelectedIndex],$scope.SatisList[$scope.IslemListeSelectedIndex].QUANTITY -1);
    } 
    $scope.BtnHesapMakinesi = function()
    {
        if(typeof require == 'undefined')
        {
            return;
        }
        const exec = require('child_process').exec;

        exec("calc", (error, stdout, stderr) => { 
            console.log(stdout); 
        });
    }
    $scope.BtnFiyatGor = function()
    {
        if($scope.Class.BtnFiyatGor == "form-group btn btn-info btn-block my-1")
            $scope.Class.BtnFiyatGor = "form-group btn btn-warning btn-block my-1"
        else
            $scope.Class.BtnFiyatGor = "form-group btn btn-info btn-block my-1"
    }
    $scope.BtnFisYazdir = function()
    {
        let TmpSeri = $scope.SonSatisList[$scope.SonSatisListeSelectedIndex].REF;
        let TmpSira = $scope.SonSatisList[$scope.SonSatisListeSelectedIndex].REF_NO;

        db.GetData($scope.Firma,'PosSatisGetir',[$scope.Sube,$scope.EvrakTip,TmpSeri,TmpSira],function(PosSatisData)
        {   
            db.GetData($scope.Firma,'PosTahGetir',[$scope.Sube,0,TmpSeri,TmpSira],function(PosTahData)
            {
                let TmpQuery = 
                {
                    db : $scope.Firma,
                    query:  "SELECT " + 
                            "CASE WHEN VAT = 20 THEN 'B' WHEN VAT = 5.5 THEN 'C' END AS VAT_TYPE, " + 
                            "VAT AS VAT, " +  
                            "(SUM(QUANTITY) * SUM(PRICE)) - (((SUM(QUANTITY) * SUM(PRICE)) / 100) * VAT) AS HT, " + 
                            "((SUM(QUANTITY) * SUM(PRICE)) / 100) * VAT AS TVA, " +
                            "ROUND(SUM(QUANTITY) * SUM(PRICE),4) AS TTC, " +
                            "ISNULL((SELECT COUNT(REF) AS TICKET FROM (SELECT REF FROM POS_SALES " + 
                            "WHERE DOC_DATE >= CONVERT(NVARCHAR(10),GETDATE(),112) " + 
                            "AND DOC_DATE <= CONVERT(NVARCHAR(10),GETDATE(),112) " + 
                            "AND DEPARTMENT = @DEPARTMENT " + 
                            "AND STATUS = 1 " + 
                            "GROUP BY REF,REF_NO) AS TMP),1) AS TICKET " + 
                            "FROM POS_SALES AS POS " +
                            "WHERE DEPARTMENT = @DEPARTMENT AND TYPE = @TYPE AND REF = @REF AND REF_NO = @REF_NO " +
                            "GROUP BY VAT",
                    param:  ['DEPARTMENT','TYPE','REF','REF_NO'],
                    type:   ['int','int','string|25','int'],
                    value:  [$scope.Sube,$scope.EvrakTip,TmpSeri,TmpSira]
                }
                db.GetDataQuery(TmpQuery,function(pData)
                {
                    db.EscposPrint(PosSatisData,PosTahData,pData,function()
                    {
                        
                    });
                });
            });
        });
    }
    //2020.09.08
    $scope.BtnProgramiKapat = function()
    {
        alertify.confirm("Programı Kapatmak İstediğinize Emin Misiniz ?",

        function()
        {
            if($scope.SatisList.length == 0)
            {
                alertify.okBtn('Evet');
                var url = "index.html";
                $window.location.href = url;
            }
            else
            {
                alertify.alert("Satış Listesi Doluyken Program Kapatılamaz.");
            }
        },
        function(){
            alertify.cancelBtn('Vazgeç');
        });
    }
    $scope.BtnAvans = async function(pTip)
    {
        for (let i = 0; i < Param.length; i++) 
        {
            if(Param[i].Yetkili && Param[i].PosSatis.Sube == $scope.Sube)
            {
                if(pTip == 1)
                {
                    if(Param[i].Sifre == $scope.TxtYetkiliSifre)
                    {
                        alert("Yetkili Şifre Doğru.");
                        $("#MdlYetkiliGiris").modal("hide");
                        angular.element('#ChkAlma').trigger('click');
                        $scope.TxtYetkiliSifre = "";
                        FocusBarkod = false;
                        FocusAraToplam = false;
                        FocusMusteri = false;
                        FocusStok = false;
                        FocusKartOdeme = false;
                        FocusYetkiliSifre = false;
                        FocusKasaSifre = false;
                        FirstKey = false;
                        FocusAvans = true;
                        
                        $("#MdlAvans").modal("show");
                    }
                    else
                    {
                        alert("Yetkili Şifre Yanlış.");
                    }
                }
                else
                {
                    $("#MdlYetkiliGiris").modal("show");
                    FocusBarkod = false;
                    FocusAraToplam = false;
                    FocusMusteri = false;
                    FocusStok = false;
                    FocusKartOdeme = false;
                    FirstKey = false;
                    FocusYetkiliSifre = true;
                }
            }
        }
    }
    $scope.BtnAvansKaydet = function()
    {
        var r = confirm("Avans Çekme İstediğinize Eminmisiniz ?");
        if (r == true) 
        {
            let TmpQuery = 
            {
                db : $scope.Firma,
                query:  "SELECT ISNULL(SUM(AMOUNT),0) - " +
                        "(SELECT ISNULL(SUM(AMOUNT),0) AS TOPLAM FROM POS_PAYMENT WHERE " +
                        "TYPE = 0 AND DOC_TYPE IN(1,3) AND DEPARTMENT = @DEPARTMENT AND CUSER = @CUSER AND DOC_DATE = @DOC_DATE) AS TOPLAM " +
                        "FROM POS_PAYMENT " +
                        "WHERE TYPE = 0 AND DOC_TYPE IN(0,2,4) AND DEPARTMENT = @DEPARTMENT AND CUSER = @CUSER AND DOC_DATE = @DOC_DATE " ,
                param:  ['DEPARTMENT','CUSER','DOC_DATE'],
                type:   ['int','string|25','date'],
                value:  [$scope.Sube,$scope.Kullanici,$scope.Tarih]
            }
            db.GetDataQuery(TmpQuery,function(pData)
            {
                let InsertData = 
                [
                    $scope.Kullanici,
                    $scope.Kullanici,
                    $scope.Sube,
                    0, //SATIŞ TİPİ(NAKİT-KREDİ KARTI)
                    $scope.AvansTip, //EVRAKTIP
                    $scope.Tarih,
                    $scope.AvansSeri,
                    $scope.AvansSira,
                    1, //CUSTOMER CODE
                    UserParam.PosSatis.NakitKasaKodu,
                    $scope.TxtAvans,
                    0, //CHANGE
                    2 //STATUS
                ];
                if($scope.TxtAvans < pData[0].TOPLAM && $scope.AvansTip == 3)
                {
                    db.ExecuteTag($scope.Firma,'PosTahInsert',InsertData,function(InsertResult)
                    {   
                        if(typeof(InsertResult.result.err) == 'undefined')
                        {                
                            $scope.TxtAvans = 0;
                            alert("Avans Çekme İşlemi Başarıyla Gerçekleşti.")
                            $("#MdlAvans").modal("hide");
                        }
                        else
                        {
                            alert("Avans Çekme İşleminde Hata.")
                        }
                    });
                }
                else if($scope.AvansTip == 4)
                {
                    db.ExecuteTag($scope.Firma,'PosTahInsert',InsertData,function(InsertResult)
                    {   
                        if(typeof(InsertResult.result.err) == 'undefined')
                        {                
                            $scope.TxtAvans = 0;
                            alert("Avans Verme İşlemi Başarıyla Gerçekleşti.")
                            $("#MdlAvans").modal("hide");
                        }
                        else
                        {
                            alert("Avans Verme İşleminde Hata.")
                        }
                    });
                }
                else
                {
                    alert("Kasanızda " + pData[0].TOPLAM + " TL Bulunmakta Avans Çekme İşlemi Reddedildi.")
                }
            });
        } 
        else 
        {
            alert("Avans Çekme İşlemi Reddedildi.")
        }
    }
    $scope.BtnAvansTip = function(pTip)
    {
        if(pTip == 0){$scope.AvansTip = 3;}else{$scope.AvansTip = 4;}
    }
    $scope.BtnPersonelSatis = function()
    {
        if($scope.Class.BtnPersonelSatis == "form-group btn btn-warning btn-block my-1")
        {
            alertify.alert("Dikkat Personel Satışı Aktifleştirildi.");
            $scope.Class.BtnPersonelSatis = "form-group btn btn-danger btn-block my-1"
            $scope.EvrakTip = 2;
        }
        else
        {
            alertify.alert("Dikkat Personel Satışı Devre Dışı Bırakıldı.");
            $scope.Class.BtnPersonelSatis = "form-group btn btn-warning btn-block my-1"
            $scope.EvrakTip = 0;
        }
    }
    async function PosPluGetir(pIndex,pType)
    {
        let PluData = await db.GetPromiseTag($scope.Firma,'PosPluGrupGetir',[$scope.Kullanici,pIndex,pType])

        if(PluData.length > 0)
        {
            for (let i = 0; i < PluData.length; i++) 
            {
                if(pType == 0 && PluData[i].LOCATION == pIndex)
                {
                    $scope.PluGrupAdi = PluData[i].NAME
                }
            }
        }
    }
    $scope.PluGetir = async function(pBarkod,pIndex,pType)
    {
        if($scope.Class.BtnEdit == "icon wb-unlock")
        {
            if(pType == 1)
            {
                $scope.DivPlu = true;
            }
                    
            $scope.Index = pIndex;
            FocusBarkod = false;
            FocusAraToplam = false;
            FocusMusteri = false;
            FocusStok = false;
            FocusMiktarGuncelle = false;
            FocusKartOdeme = false;
            FocusYetkiliSifre = false;
            FocusAvans = false;
            await PosPluGetir(pIndex,pType);
            $("#MdlPluEdit").modal("show");
        }
        else
        {
            if(pType == 0)
            {
                db.GetData($scope.Firma,'PosPluGrupGetir',[$scope.Kullanici,pIndex,pType],function(PluData)
                {
                    $scope.PluGrupIndex = PluData[0].GRUP_INDEX;
                    if(PluData.length > 0)
                    {
                        db.GetData($scope.Firma,'PosPluGrupGetir',[$scope.Kullanici,PluData[0].GRUP_INDEX,1],function(PluData)
                        {
                            $scope.PluList = PluData;
                        });
                    }
                });
            }
            else if (pType == 1)
            {
                $scope.TxtBarkod = pBarkod;
                $scope.StokGetir($scope.TxtBarkod);
            }
        }
    }
    $scope.BtnEdit = function()
    {
        if($scope.Class.BtnEdit == "icon wb-lock")
        {
            alertify.alert("Dikkat Plu Düzenleme Aktifleştirildi.");
            $scope.Class.BtnEdit = "icon wb-unlock"
        }
        else
        {
            alertify.alert("Dikkat Plu Düzenleme Devre Dışı Bırakıldı.");
            $scope.Class.BtnEdit = "icon wb-lock"
        }
    }
    $scope.BtnPluKaydet = async function()
    {
        if($scope.DivPlu) //GRUP INSERT Mİ PLU İNSERT Mİ İŞLEMİNİ BURADAN ANLIYORUZ.
        {
            let PluData = await db.GetPromiseTag($scope.Firma,'PosPluGetir',[$scope.Kullanici,$scope.Index,$scope.PluGrupIndex,1])
            
            if(PluData.length == 0)
            {
                let InsertData = 
                [
                    UserParam.Kullanici,
                    UserParam.Kullanici,
                    $scope.Tarih,
                    $scope.Tarih,
                    $scope.PluGrupAdi,
                    $scope.Index,
                    1, //TYPE
                    $scope.PluStokKod,//ITEMS CODE
                    $scope.PluGrupIndex  //GRUPINDEX
                ]
    
                db.ExecuteTag($scope.Firma,'PosPluInsert',InsertData,function(InsertResult)
                {
                    if(typeof(InsertResult.result.err) == 'undefined')
                    {   
                        alert("Kayıt İşlemi Başarıyla Gerçekleşti.")
                        $("#MdlPluEdit").modal("hide");
                        $scope.PluGrupAdi = "";
                        $scope.Index = "";
                        $scope.PluStokKod = "";
                        $scope.YeniEvrak();
                    }
                    else
                    {
                        console.log(InsertResult.result.err);
                    }
                });
            }
            else
            {
                db.ExecuteTag($scope.Firma,'PosPluUpdate',[$scope.PluGrupAdi,$scope.PluStokKod,1,$scope.Index,PluData[0].GRUP_INDEX],function(InsertResult)
                {
                    if(typeof(InsertResult.result.err) == 'undefined')
                    {   
                        alert("Güncelleme İşlemi Başarıyla Gerçekleşti.")
                        $("#MdlPluEdit").modal("hide");
                        $scope.PluGrupAdi = "";
                        $scope.Index = "";
                        $scope.PluStokKod = "";
                        $scope.YeniEvrak();
                    }
                    else
                    {
                        console.log(InsertResult.result.err);
                    }
                });
            }
        }
        else
        {
            let PluData = await db.GetPromiseTag($scope.Firma,'PosPluGrupGetir',[$scope.Kullanici,$scope.Index,0])
            if(PluData.length == 0)
            {
                let InsertData = 
                [
                    UserParam.Kullanici,
                    UserParam.Kullanici,
                    $scope.Tarih,
                    $scope.Tarih,
                    $scope.PluGrupAdi,
                    $scope.Index,
                    0, //TYPE
                    '',//ITEMS CODE
                    $scope.Index  //GRUPINDEX
                ]
    
                db.ExecuteTag($scope.Firma,'PosPluInsert',InsertData,function(InsertResult)
                {
                    if(typeof(InsertResult.result.err) == 'undefined')
                    {   
                        alert("Kayıt İşlemi Başarıyla Gerçekleşti.")
                        $("#MdlPluEdit").modal("hide");
                        $scope.PluGrupAdi = "";
                        $scope.Index = "";
                        $scope.YeniEvrak();
                    }
                    else
                    {
                        console.log(InsertResult.result.err);
                    }
                });
            }
            else
            {
                db.ExecuteTag($scope.Firma,'PosPluGrupUpdate',[$scope.PluGrupAdi,'',$scope.Index,0,$scope.Index],function(InsertResult)
                {
                    if(typeof(InsertResult.result.err) == 'undefined')
                    {   
                        alert("Güncelleme İşlemi Başarıyla Gerçekleşti.")
                        $("#MdlPluEdit").modal("hide");
                        $scope.PluGrupAdi = "";
                        $scope.Index = "";
                        $scope.YeniEvrak();
                    }
                    else
                    {
                        console.log(InsertResult.result.err);
                    }
                });
            }
        }
    }
    $scope.BtnIadeAl = function()
    {
        if($scope.SatisList.length == 0)
        {
            $scope.Class.BtnIadeAl = "form-group btn btn-primary btn-block my-1";
            alertify.alert("İade İşlemi İçin Fiyat Güncelleme Aktifleştirildi.")
        }
        else
        {
            alertify.okBtn('Evet');
            alertify.cancelBtn('Hayır');
            alertify.confirm('İade Almak İstediğinize Emin Misiniz ?', 
            function()
            { 
                //POS SATIS UPDATE
                var TmpQuery = 
                {
                    db : $scope.Firma,
                    query:  "UPDATE POS_SALES SET LDATE = GETDATE(),TYPE = 1,STATUS = 1,REF = @IREF,REF_NO = @IREF_NO WHERE DEPARTMENT = @DEPARTMENT AND TYPE = 0 AND REF = @SREF AND REF_NO = @SREFNO",
                    param:  ['IREF','IREF_NO','DEPARTMENT','SREF','SREFNO'],
                    type:   ['string|25','int','int','string|25','int'],
                    value:  [$scope.IadeSeri,$scope.IadeSira,$scope.Sube,$scope.Seri,$scope.Sira]
                }
                db.ExecuteQuery(TmpQuery,function(UpdateResult)
                {
                    if(typeof(UpdateResult.result.err) == 'undefined')
                    {                       
                        var InsertData = 
                        [
                            UserParam.Kullanici,
                            UserParam.Kullanici,
                            $scope.Sube,
                            0, //TYPE
                            1, //DOC_TYPE
                            $scope.Tarih,
                            $scope.IadeSeri,
                            $scope.IadeSira,
                            $scope.CariKodu,
                            UserParam.PosSatis.NakitKasaKodu,
                            $scope.GenelToplam,
                            0, //PARA USTU
                            1
                        ];
            
                        db.ExecuteTag($scope.Firma,'PosTahInsert',InsertData,function(InsertResult)
                        {
                            if(typeof(InsertResult.result.err) == 'undefined')
                            {                       
                                $scope.YeniEvrak();
                                $scope.TxtBarkod = "";
                            }
                            else
                            {
                                console.log(InsertResult.result.err);
                            }
                        });    
                    }
                    else
                    {
                        console.log(UpdateResult.result.err);
                    }
                });
            }
            ,function(){});
        }
    }
    $scope.BtnKasaKilitle = function(pTip)
    {
        if(pTip == 0)
        {
            alertify.okBtn('Evet');
            alertify.cancelBtn('Hayır');
            alertify.confirm('Kasayı Kilitlemek İstediğinize Emin Misiniz ?', 
            function()
            { 
                $('#MdlKasaSifre').modal({backdrop: 'static', keyboard: false})
                FocusBarkod = false;
                FocusAraToplam = false;
                FocusMusteri = false;
                FocusStok = false;
                FocusKartOdeme = false;
                FirstKey = false;
                FocusYetkiliSifre = false;
                FocusKasaSifre = true;
            }
            ,function(){});
        }
        else
        {
            for (let i = 0; i < Param.length; i++) 
            {
                if(Param[i].PosSatis.Sube == $scope.Sube)
                {
                    if(Param[i].Sifre == $scope.TxtKasaSifre && Param[i].Kullanici == $scope.Kullanici)
                    {
                        $scope.TxtKasaSifre = "";
                        $("#MdlKasaSifre").modal("hide");
                        alert("Şifre Kabul Edildi.")
                        return;
                    }
                    else if(Param[i].Yetkili && Param[i].Sifre == $scope.TxtKasaSifre)
                    {
                        $scope.TxtKasaSifre = "";
                        $("#MdlKasaSifre").modal("hide");
                        alert("Yetkili Girişi Kabul Edildi.")
                        return;
                    }
                    else
                    {
                        if(Param[i].Kullanici == $scope.Kullanici)
                        {
                            alert("Şifre Reddedildi.")
                        }
                    }
                }
            }
        }
    }
    $scope.BtnKasaRapor = function()
    {
        db.GetData($scope.Firma,'PosAraToplamRapor',[$scope.Sube,$scope.Tarih,$scope.Kullanici],function(AraToplamRapor)
        {  
            $scope.AraToplamRaporList = AraToplamRapor;
            $("#TblAraToplam").jsGrid({data : $scope.AraToplamRaporList});
            $scope.TxtBarkod = "";
        });
        db.GetData($scope.Firma,'PosAraToplamKasaRapor',[$scope.Sube,$scope.Tarih,$scope.Kullanici],function(KasaAraToplamRapor)
        {  
            $scope.KasaAraToplamRaporList = KasaAraToplamRapor;
            $("#TblKasaAraToplam").jsGrid({data : $scope.KasaAraToplamRaporList});
            $scope.TxtBarkod = "";
        });

        $("#TbKasaRapor").addClass('active');
        $("#TbMain").removeClass('active');
    }
    $scope.BtnOkcEslesme = function()
    {
        if($scope.BtnTxtOkcEslesme == "İptal")
        {
            $('#MdlIngenicoEslesme').modal('hide');
        }
        else
        {
            if(typeof require != 'undefined')
            {
                $scope.TxtOkcMesaj = "OKC Cihazıyla Eşleşme Yapılıyor.";
                $scope.BtnTxtOkcEslesme = "İptal"
                $("#MdlIngenicoEslesme").modal("show");  
                db.Ingenico.Init();
            }
        }
    }
}