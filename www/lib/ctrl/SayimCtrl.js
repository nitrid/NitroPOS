function SayimCtrl($scope,$window,$timeout,db)  
{
    let IslemSelectedRow = null;
    let StokSelectedRow = null;
    $scope.CmbEvrakTip = '0';

    function Init()
    {
        $scope.Firma = $window.sessionStorage.getItem('Firma');
        UserParam = Param[$window.sessionStorage.getItem('User')];
        
        $scope.EvrakNo;
        $scope.Barkod = "";
        $scope.Tarih = new Date().toLocaleDateString('tr-TR',{ year: 'numeric', month: 'numeric', day: 'numeric' });
        $scope.DepoNo;
        $scope.DepoAdi = "";

        $scope.Birim = 0;
        $scope.StokGridTip = "0";
        $scope.StokGridText = "";

        $scope.DepoListe = [];
        $scope.SayimListe = [];
        $scope.BirimListe = [];
        $scope.StokListe = [];
        $scope.Stok = [];

        $scope.ToplamMiktar1 = 0;
        $scope.ToplamMiktar2 = 0;
        $scope.ToplamMiktar3 = 0;
        $scope.ToplamMiktar4 = 0;
        $scope.ToplamMiktar5 = 0;
        $scope.ToplamSatir = 0;
        
        $scope.Miktar = 1;

        // DÜZENLE MODAL
        $scope.MiktarEdit = 0;

        $scope.OtoEkle = false;
        $scope.EvrakLock = false;
        $scope.BarkodLock = false; 
        $scope.IslemListeSelectedIndex = -1; 
        $scope.CmbEvrakTip = "10";

        $scope.Loading = false;
        $scope.TblLoading = true;

        
    }
    function InitIslemGrid()
    {
        $("#TblIslem").jsGrid({
            responsive: true,
            width: "100%",
            height: "350px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.SayimListe,
            paging : true,
            pageSize: 50,
            pageButtonCount: 3,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
           
            fields: 
            [
            {
                name: "NO",
                title: "NO",
                type: "number",
                align: "center",
                width: 75
                
            }, 
            {
                name: "sym_Stokkodu",
                title: "KODU",
                type: "text",
                align: "center",
                width: 100
            },
            {
                name: "ADI",
                title: "ADI",
                type: "text",
                align: "center",
                width: 200
            }, 
            {
                name: "sym_miktar1",
                title: "SAYIM1",
                type: "number",
                align: "center",
                width: 100
            }, 
            {
                name: "sym_miktar2",
                title: "SAYIM2",
                type: "number",
                align: "center",
                width: 100
            }, 
            {
                name: "sym_miktar3",
                title: "SAYIM3",
                type: "number",
                align: "center",
                width: 100
            }, 
           ],
            rowClick: function(args)
            {
                $scope.IslemListeRowClick(args.itemIndex,args.item,this);
                $scope.$apply();
            }
        });
    }
    function InitStokGrid()
    {
        $("#TblStok").jsGrid
        ({
            width: "100%",
            height: "500px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.StokListe,
            fields: [
                {
                    name: "KODU",
                    title: "KODU",
                    type: "text",
                    align: "center",
                    width: 125
                }, 
                {
                    name: "ADI",
                    title: "ADI",
                    type: "text",
                    align: "center",
                    width: 200
                }, 
                {
                    name: "DEPOMIKTAR",
                    title: "DEPO MIKTAR",
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
    function ToplamMiktarHesapla()
    {
       $scope.ToplamMiktar1 = 0;
       $scope.ToplamMiktar2 = 0;
       $scope.ToplamMiktar3 = 0;
       $scope.ToplamMiktar4 = 0;
       $scope.ToplamMiktar5 = 0;
       $scope.ToplamSatir = 0;

       angular.forEach($scope.SayimListe,function(value)
       {
           $scope.ToplamMiktar1 += value.sym_miktar1;
           $scope.ToplamMiktar2 += value.sym_miktar2;
           $scope.ToplamMiktar3 += value.sym_miktar3;
           $scope.ToplamMiktar4 += value.sym_miktar4;
           $scope.ToplamMiktar5 += value.sym_miktar5;
           $scope.ToplamSatir += 1;
       });
    }
    function BarkodFocus()
    {
        $timeout( function(){$window.document.getElementById("Barkod").focus();},100);
    }
    function InsertAfterRefresh(pData)
    {      
        $scope.EvrakLock = true;
        $scope.BarkodLock = false;
        $scope.SayimListe = pData;        
        $scope.BtnTemizle();        
        $window.document.getElementById("Barkod").focus();
        ToplamMiktarHesapla();        
    }  
    function InsertData()
    {      
         var InsertData = 
        [
            UserParam.MikroId,
            UserParam.MikroId,
            $scope.Tarih,
            $scope.DepoNo,
            $scope.EvrakNo,
            $scope.Stok[0].KODU,
            $scope.Miktar * $scope.Stok[0].CARPAN,
            $scope.Stok[0].BIRIMPNTR,
            $scope.Stok[0].BARKOD,
            0,
            0,
            '',
            0,
            ''
        ];
        
        db.ExecuteTag($scope.Firma,'SayimInsert',InsertData,function(InsertResult)
        {    
            if(typeof(InsertResult.result.err) == 'undefined')
            {     
                if(localStorage.mode == 'true')
                {
                    $scope.SayimListe.push(InsertResult.result.recordset[0]);
                    InsertAfterRefresh($scope.SayimListe); 
                    $scope.InsertLock = false;
                    if(UserParam.Sistem.Titresim == 1)
                    {
                        Confirmation();
                    }
                }
                else
                {
                    var TmpQuery = 
                    {
                        db : '{M}.' + $scope.Firma,
                        query:  "SELECT IFNULL((SELECT ADI FROM STOK WHERE KODU = sym_Stokkodu),'') AS ADI, " +
                                "sym_satirno AS NO, " +
                                "* FROM SAYIM WHERE sym_tarihi = @sym_tarihi AND " +
                                "sym_depono = @sym_depono AND sym_evrakno = @sym_evrakno " + 
                                "AND sym_satirno = (SELECT IFNULL(MAX(sym_satirno),0) FROM SAYIM WHERE sym_evrakno=@sym_evrakno AND sym_depono=@sym_depono AND sym_tarihi='@sym_tarihi') ORDER BY sym_lastup_date ASC ",
                        param:  ['sym_tarihi','sym_depono','sym_evrakno'],
                        type:   ['date','int','int'],
                        value:  [$scope.Tarih,$scope.DepoNo,$scope.EvrakNo]
                    }
                    db.GetDataQuery(TmpQuery,function(SayimData)
                    {
                        $scope.SayimListe.push(SayimData[0]);
                        InsertAfterRefresh($scope.SayimListe);     
                        $scope.InsertLock = false  
                        if(UserParam.Sistem.Titresim == 1)
                        {
                            Confirmation();
                        }
                    });
                }
            }
            else
            {
                console.log(InsertResult.result.err);
            }
        });
    }
    function UpdateData(pData) 
    {   
        db.ExecuteTag($scope.Firma,'SayimUpdate',pData.Param,function(InsertResult)
        {  
            if(typeof(InsertResult.result.err) == 'undefined')
            {   
                db.GetData($scope.Firma,'SayimGetir',[$scope.DepoNo,$scope.EvrakNo,$scope.Tarih],function(SayimData)
                {
                    $("#TblIslem").jsGrid({data : $scope.SayimListe});
                    InsertAfterRefresh(SayimData);
                    Confirmation();
                    //ToplamMiktarHesapla();
                });
            }
            else
            {
                console.log(InsertResult.result.err);
            }
        });
    }
    function StokBarkodGetir(pBarkod)
    {
        if(pBarkod != '')
        {
            db.StokBarkodGetir($scope.Firma,pBarkod,$scope.DepoNo,function(BarkodData)
            {   
                if(BarkodData.length > 0)
                {
                    $scope.Stok = BarkodData;

                    $scope.StokKodu = $scope.Stok[0].KODU;
                    $scope.Stok[0].TOPMIKTAR = 1;

                    db.GetData($scope.Firma,'CmbBirimGetir',[BarkodData[0].KODU],function(data)
                    {
                        $scope.BirimListe = data; 
                        $scope.Birim = JSON.stringify($scope.Stok[0].BIRIMPNTR);

                        if($scope.BirimListe.length > 0)
                        {
                            $scope.Stok[0].BIRIMPNTR = $scope.BirimListe.filter(function(d){return d.BIRIMPNTR == $scope.Birim})[0].BIRIMPNTR;
                            $scope.Stok[0].BIRIM = $scope.BirimListe.filter(function(d){return d.BIRIMPNTR == $scope.Birim})[0].BIRIM;
                            $scope.Stok[0].CARPAN = $scope.BirimListe.filter(function(d){return d.BIRIMPNTR == $scope.Birim})[0].KATSAYI;
                            $scope.MiktarFiyatValid();
                        }
                        if($scope.OtoEkle == true)
                        {
                            $scope.Insert()
                        }
                        else
                        {
                            $window.document.getElementById("Miktar").focus();
                            $window.document.getElementById("Miktar").select();
                        }
                    });                   
                }
                else
                {                        
                    Beep();
                    console.log("Stok Bulunamamıştır.");
                }
            });
        }
    }
    function Beep()
    {
        navigator.notification.vibrate(1000);
        //navigator.vibrate([100,100,200,100,300]);
        document.getElementById("Beep").play();
    }
    function Confirmation()
    {
        navigator.vibrate([100,100,200,100,300]);
    }
    function AktarimSiraGetir(pSira,pTarih,pDepo,pCallback)
    {
        localStorage.mode = 'true';
        var TmpQuery = 
        {
            db : '{M}.' + $scope.Firma,
            query:  "SELECT " +
                    "CASE WHEN MAX(sym_evrakno) IS NOT NULL THEN " +
                    "(SELECT ISNULL(MAX(sym_evrakno),0) + 1 FROM SAYIM_SONUCLARI WHERE sym_tarihi = @sym_tarihi AND sym_depono = @sym_depono) " +
                    "ELSE " +
                    "@sym_evrakno END AS EVRAKNO " +
                    "FROM SAYIM_SONUCLARI WHERE sym_tarihi = @sym_tarihi AND sym_depono = @sym_depono AND sym_evrakno = @sym_evrakno",
            param:  ['sym_tarihi','sym_depono','sym_evrakno'],
            type:   ['date','int','int'],
            value:  [pTarih,pDepo,pSira]
        }

        db.GetDataQuery(TmpQuery,function(data)
        {
            localStorage.mode = 'false';
            pCallback(data[0].EVRAKNO);
        });
    }
    $scope.YeniEvrak = async function()
    {
        Init();
        InitIslemGrid();
        InitStokGrid();
     
        $scope.EvrakLock = false;
        $scope.DepoNo = UserParam.Sayim.DepoNo;
        $scope.CmbEvrakTip = "0";
        $scope.Stok = 
        [
            {
                BIRIM : '',
                BIRIMPNTR : 0, 
                TOPMIKTAR : 0
            }
        ];
     
        db.FillCmbDocInfo($scope.Firma,'CmbDepoGetir',function(data)
        {
            console.log(1)
            $scope.DepoListe = data; 
            $scope.DepoNo = UserParam.Sayim.DepoNo;
            
            $scope.DepoListe.forEach(function(item) 
            {
                if(item.KODU == $scope.DepoNo)
                    $scope.DepoAdi = item.ADI;
            });     
        });
        
       await db.MaxSiraPromiseTag($scope.Firma,'MaxSayimSira',[$scope.DepoNo,$scope.Tarih],function(data)
        {  
            $scope.EvrakNo = data
        });
        
        BarkodFocus();
    }
    $scope.BtnStokGridGetir = function()
    {
        let Kodu = '';
        let Adi = '';
        $scope.Loading = true;
        $scope.TblLoading = false;

        if($scope.StokGridTip == "0")
        {   
            Adi = $scope.StokGridText.replace("*","%").replace("*","%");
        }
        else
        {
            Kodu = $scope.StokGridText.replace("*","%").replace("*","%");
        }
            
        db.GetData($scope.Firma,'StokGetir',[Kodu,Adi,$scope.DepoNo,''],function(StokData)
        {
            $scope.StokListe = StokData;
            if($scope.StokListe.length > 0)
            {
                $scope.Loading = false;
                $scope.TblLoading = true;
                $("#TblStok").jsGrid({data : $scope.StokListe});
            }
            else
            {
                $("#TblStok").jsGrid({data : $scope.StokListe});
            }
        });
    }
    $scope.BtnStokGridSec = function()
    {
        $("#MdlStokGetir").modal('hide');

        StokBarkodGetir($scope.Barkod);
        $scope.Barkod = "";
    }
    $scope.BtnStokBarkodGetir = function(keyEvent)
    {
        if(keyEvent.which === 13)
        {
            StokBarkodGetir($scope.Barkod);  
            $scope.Barkod = "";    
        }
    }
    $scope.MiktarFiyatValid = function()
    {
        $scope.Stok[0].TOPMIKTAR = $scope.Stok[0].CARPAN * $scope.Miktar
    }
    $scope.IslemListeRowClick = function(pIndex,pItem,pObj)
    {
        if ( IslemSelectedRow ) { IslemSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = pObj.rowByItem(pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        IslemSelectedRow = $row;
        $scope.IslemListeSelectedIndex = pIndex;
    }
    $scope.StokListeRowClick = function(pIndex,pItem,pObj)
    {
        if ( StokSelectedRow ) { StokSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = pObj.rowByItem(pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        StokSelectedRow = $row;
        
        $scope.Barkod = $scope.StokListe[pIndex].KODU;
    }
    $scope.BtnTemizle = function()
    {   
        $scope.DepoMiktar = 0;
        $scope.KalanMiktar = 0;
        //$scope.Barkod = "";
        $scope.Stok = null;
        $scope.Stok = 
        [
            {
                BIRIM : '',
                BIRIMPNTR : 0, 
                TOPMIKTAR : 0
            }
        ];
        $scope.Miktar = 1;
        //ENKAY İÇİ YAPILDI
        
        $scope.BarkodLock = false;
        
        $scope.BirimListe = [];
        BarkodFocus();      
    }
    $scope.BtnDuzenle = function()
    {
        $scope.MiktarEdit = $scope.SayimListe[$scope.IslemListeSelectedIndex].sym_miktar1;
        $("#MdlDuzenle").modal('show');
    }
    $scope.BtnDuzenleKaydet = function(pIndex)
    {
        let TmpMiktar = $scope.MiktarEdit;

        $scope.SayimListe[pIndex].sym_miktar1 = TmpMiktar;

        $scope.Update(pIndex);
        angular.element('#MdlDuzenle').modal('hide');
    }
    $scope.MiktarPress = function(keyEvent)
    {
        if(keyEvent.which == 40)
        {
            $window.document.getElementById("Miktar").focus();
            $window.document.getElementById("Miktar").select();
        }
        if(keyEvent.which == 13)
        {
            $scope.Insert();
        }
    }
    $scope.BirimChange = function()
    {
        if($scope.BirimListe.length > 0)
        {
            $scope.Stok[0].BIRIMPNTR = $scope.BirimListe.filter(function(d){return d.BIRIMPNTR == $scope.Birim})[0].BIRIMPNTR;
            $scope.Stok[0].BIRIM = $scope.BirimListe.filter(function(d){return d.BIRIMPNTR == $scope.Birim})[0].BIRIM;
            $scope.Stok[0].CARPAN = $scope.BirimListe.filter(function(d){return d.BIRIMPNTR == $scope.Birim})[0].KATSAYI;
            $scope.MiktarFiyatValid();
        }
    }
    $scope.Insert = function()
    { 
        $scope.InsertLock = true

        if(typeof($scope.Stok[0].KODU) != 'undefined')
        {   
            if(UserParam.Sistem.SatirBirlestir == 0 || $scope.Stok[0].RENKPNTR != 0 || $scope.Stok[0].BEDENPNTR != 0 || $scope.Stok[0].DETAYTAKIP == 1 || $scope.Stok[0].DETAYTAKIP == 2)
            {
                InsertData();
            }
            else
            {   
                let UpdateStatus = false;

                angular.forEach($scope.SayimListe,function(value)
                {   
                    if($scope.CmbEvrakTip == 0)
                    {
                        if(value.sym_Stokkodu == $scope.Stok[0].KODU)
                        {   
                            let TmpMiktar = value.sym_miktar1 + ($scope.Miktar * $scope.Stok[0].CARPAN);
                            let Data = 
                            {
                                Param :
                                [
                                    TmpMiktar,
                                    value.sym_miktar2,
                                    0,
                                    0,
                                    0,
                                    value.sym_Guid
                                ],
                                Miktar : $scope.Miktar * $scope.Stok[0].CARPAN
                            };

                            UpdateStatus = true;
                            UpdateData(Data);
                            $scope.InsertLock = false 
                        }  
                    }   
                    if($scope.CmbEvrakTip == 1)
                    {
                        if(value.sym_Stokkodu == $scope.Stok[0].KODU)
                        {   
                            let TmpMiktar = value.sym_miktar2 + ($scope.Miktar * $scope.Stok[0].CARPAN);
                            let Data = 
                            {
                                Param :
                                [
                                    value.sym_miktar1,
                                    TmpMiktar,
                                    0,
                                    0,
                                    0,
                                    value.sym_Guid
                                ],
                                Miktar : $scope.Miktar * $scope.Stok[0].CARPAN
                            };

                            UpdateStatus = true;
                            UpdateData(Data);
                            $scope.InsertLock = false 
                        }     
                    }                   
                });

                if(!UpdateStatus)
                {   
                    InsertData();
                    $scope.InsertLock = false 
                }                
            }
        }
        else
        {
            console.log("Barkod Okutunuz!");
            $scope.InsertLock = false
        }

        $scope.DepoMiktar = 0;
        $scope.KalanMiktar = 0;
        BarkodFocus();
    }
    $scope.BtnBarkodGetirClick = function()
    {
        StokBarkodGetir($scope.Barkod);
    }
    $scope.EvrakGetir = function ()
    {   
        db.GetData($scope.Firma,'SayimGetir',[$scope.DepoNo,$scope.EvrakNo,$scope.Tarih],function(data)
        {   
            if(data.length > 0)
            {
                Init();
                InitIslemGrid();
                
                $scope.DepoNo = data[0].sym_depono.toString();
                $scope.EvrakNo = data[0].sym_evrakno.toString();
                $scope.Tarih = moment(data[0].sym_tarihi).format("DD.MM.YYYY");
                
                $scope.Barkod = "";
                $scope.Stok = 
                [
                    {
                        BIRIM : '',
                        BIRIMPNTR : 0, 
                        TOPMIKTAR : 0
                    }
                ];
                $scope.Miktar = 1;
                
                $scope.ToplamMiktar1 = 0;
                $scope.ToplamMiktar2 = 0;
                $scope.ToplamMiktar3 = 0;
                $scope.ToplamMiktar4 = 0;
                $scope.ToplamMiktar5 = 0;
            
                $scope.TOPMIKTAR = 0;

                db.DepoGetir($scope.Firma,UserParam.Sayim.DepoListe,function(e)
                {
                    $scope.DepoListe = e; 
                    $scope.DepoNo = data[0].sym_depono.toString();
                    $scope.DepoListe.forEach(function(item) 
                    {
                        if(item.KODU == $scope.DepoNo)
                            $scope.DepoAdi = item.ADI;
                    });     
                });

                $scope.SayimListe = data;
                $("#TblIslem").jsGrid({data : $scope.SayimListe});
            
                ToplamMiktarHesapla();

                $scope.EvrakLock = true;
                $scope.BarkodLock = false;

                angular.element("#MdlEvrakGetir").modal('hide');

                BarkodFocus();
            }
            else
            {
                angular.element('#MdlEvrakGetir').modal('hide');
                alertify.okBtn("Tamam");
                alertify.alert("Belge Bulunamadı!");
            }
        });
    }
    $scope.EvrakDelete = function()
    {
        alertify.okBtn('Evet');
        alertify.cancelBtn('Hayır');

        alertify.confirm('Bu Belgeyi Silmek İstediğinize Eminmisiniz ?', 
        function()
        {   
            if($scope.SayimListe.length > 0)
            {
                if(UserParam.Sayim.EvrakSil == 0)
                {
                    db.ExecuteTag($scope.Firma,'SayimEvrDelete',[$scope.EvrakNo,$scope.Tarih,$scope.DepoNo],function(data)
                    {
                        $scope.YeniEvrak();
                    });
                }
                else
                {
                    alertify.okBtn("Tamam");
                    alertify.alert("Belge Silme Yektini Yok !");
                }
            }
            else
            {
                alertify.okBtn("Tamam");
                alertify.alert("Silinecek Belge Yok !");
            }
        });
    }
    $scope.SatirDelete = function()
    {
        alertify.okBtn('Evet');
        alertify.cancelBtn('Hayır');

        alertify.confirm('Bu Satırı Silmek İstediğinize Eminmisiniz?', 
        function()
        { 
            if($scope.IslemListeSelectedIndex > -1)
            {   
                if(UserParam.Sayim.EvrakSil == 0)
                {  
                    db.ExecuteTag($scope.Firma,'SayimSatirDelete',[$scope.SayimListe[$scope.IslemListeSelectedIndex].sym_Guid],function(data)
                    {   
                        if($scope.SayimListe.length <= 1)
                        {
                            $scope.YeniEvrak();
                        }
                        else
                        {
                            db.GetData($scope.Firma,'SayimGetir',[$scope.DepoNo,$scope.EvrakNo,$scope.Tarih],function(data)
                            {   
                                $scope.SayimListe = data;
                                
                                $("#TblIslem").jsGrid({data : $scope.SayimListe});    
                                $scope.BtnTemizle();
                                ToplamMiktarHesapla();
                            });
                        }
                    });
                }
                else
                {
                    alertify.okBtn("Tamam");
                    alertify.alert("Belge Silme Yetkiniz Yok!");
                }
            }
            else
            {
                alertify.okBtn("Tamam");
                alertify.alert("Satır Seçmeden Silemezsiniz !");
            }
        });
    }
    $scope.Update = function(pIndex)
    {   
        let Data = 
        {
            Param :
            [   
                $scope.MiktarEdit,
                1,
                1,
                1,
                1,
                $scope.SayimListe[pIndex].sym_Guid
            ],
            Miktar :  $scope.MiktarEdit
        };

        UpdateData(Data);
    }
    $scope.MainClick = function() 
    {
        $("#TbMain").addClass('active');
        $("#TbBelgeBilgisi").removeClass('active');
        $("#TbBarkodGiris").removeClass('active');
        $("#TbIslemSatirlari").removeClass('active');
    }
    $scope.BelgeBilgisiClick = function() 
    {
        $("#TbBelgeBilgisi").addClass('active');
        $("#TbMain").removeClass('active');
    }
    $scope.BarkodGirisClick = function()
    {   
        if($scope.EvrakNo == 0 || typeof $scope.EvrakNo == "undefined")
        {            
            alertify.alert("<a style='color:#3e8ef7''>" + "Lütfen Evrak Siranın Gelmesini Bekleyin!" + "</a>" );
        }
        else
        {
            $("#TbBarkodGiris").addClass('active');
            $("#TbMain").removeClass('active');
            $("#TbBelgeBilgisi").removeClass('active');
            $("#TbIslemSatirlari").removeClass('active');
            BarkodFocus();
        }
    }
    $scope.TbIslemSatirlariClick = function()
    {   
        if($scope.ToplamSatir <= 0)
        {
            alertify.alert("Gösterilecek Belge Yok!");
            $("#TbMain").addClass('active');
            $("#TbIslemSatirlari").removeClass('active');
            $("#TbBarkodGiris").removeClass('active');
        }
        else
        {
            $("#TbIslemSatirlari").addClass('active');
            $("#TbMain").removeClass('active');
            $("#TbBelgeBilgisi").removeClass('active');
            $("#TbBarkodGiris").removeClass('active');
            
            db.GetData($scope.Firma,'SayimGetir',[$scope.DepoNo,$scope.EvrakNo,$scope.Tarih],function(SayimData)
            {   
                InsertAfterRefresh(SayimData);     
                $("#TblIslem").jsGrid({data : $scope.SayimListe});           
            });            
        }
    }
    $scope.PageRefresh = function()
    {
        $scope.DepoListe.forEach(function(item) 
        {
            if(item.KODU == $scope.DepoNo)
                $scope.DepoAdi = item.ADI;
        });
    }
    $scope.EvrakGonder = async function()
    {
        if(localStorage.mode == 'false')
        {
            await db.ConnectionPromise(function(Status)
            {
                if(!Status)
                {
                    alertify.okBtn("Tamam");
                    alertify.alert("Bağlantı Problemi !");
                    return;
                }
            });

            AktarimSiraGetir($scope.SayimListe[0].sym_evrakno,$scope.SayimListe[0].sym_tarihi,$scope.SayimListe[0].sym_depono,async function(EvrakNo)
            {
                alertify.okBtn("Tamam");
                alertify.alert("Sayım fişi aktarımı başladı.");

                for(i = 0;i < $scope.SayimListe.length;i++)
                {
                    localStorage.mode = 'true';

                    var InsertData = 
                    [
                        $scope.SayimListe[i].sym_create_user,
                        $scope.SayimListe[i].sym_lastup_user,
                        $scope.SayimListe[i].sym_tarihi,
                        $scope.SayimListe[i].sym_depono,
                        EvrakNo,
                        $scope.SayimListe[i].sym_Stokkodu,
                        $scope.SayimListe[i].sym_miktar1,
                        $scope.SayimListe[i].sym_birim_pntr,
                        $scope.SayimListe[i].sym_barkod,
                        $scope.SayimListe[i].sym_renkno,
                        $scope.SayimListe[i].sym_bedenno,
                        $scope.SayimListe[i].sym_parti_kodu,
                        $scope.SayimListe[i].sym_lot_no,
                        $scope.SayimListe[i].sym_serino
                    ];
                    
                    await db.ExecutePromiseTag($scope.Firma,'SayimInsert',InsertData,function(InsertResult)
                    {    
                        if(typeof(InsertResult.result.err) != 'undefined')
                        {
                            console.log(InsertResult.result.err);
                        }
                        localStorage.mode = 'false';
                    });    
                }

                alertify.alert("Sayım fişi aktarımı tamamlandı.");
            });
        }
        else
        {
            alertify.okBtn("Tamam");
            alertify.alert("Bu menü sadece offline mod'da çalışır !");
        }
    }
    $scope.EvrakTipChange = function()
    {
        if(CmbEvrakTip == 0)
        {
            $scope.OtoEkle = false
        }
    }
    $scope.ScanBarkod = function()
    {
        cordova.plugins.barcodeScanner.scan(
            function (result) 
            {
                $scope.Barkod = result.text;
                StokBarkodGetir($scope.Barkod);
            },
            function (error) 
            {
                //alert("Scanning failed: " + error);
            },
            {
                prompt : "Barkod Okutunuz",
                orientation : "portrait"
            }
        );
    }
} 