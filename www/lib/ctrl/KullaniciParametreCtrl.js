function KullaniciParametreCtrl($route,$scope,$window,$rootScope,db)
{
    let KullaniciListeRow = null;
    $('#MdlKullanici').on('hide.bs.modal', function () 
    {
        $scope.Kullanici = "";
        $scope.Sifre = "";
        $scope.Kodu = "";
    });
    $('#MdlKullaniciGuncelle').on('hide.bs.modal', function () 
    {
        $scope.Kullanici = "";
        $scope.Sifre = "";
        $scope.Kodu = "";
    });
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
        //KULLANICI
        $scope.Kodu = "";
        $scope.Kullanici = "";
        $scope.Sifre = "";
        $scope.Yetki = "0";
        $scope.KullaniciGuid = "";
        $scope.AktifPasif = true;
        //SİSTEM
        $scope.KiloBarkod = "";
        $scope.KiloFlag = "";
        $scope.KiloBaslangic = "";
        $scope.KiloUzunluk = "";
        $scope.SatirBirlestir = 0;
        //POSSATIŞ
        $scope.SatisSeri = "IRS";
        $scope.TahsilatSeri = "THS";
        $scope.IadeSeri = "IADE";
        $scope.AvansSeri = "AVNS";
        $scope.CariKodu = "1";
        $scope.NKasaKodu = "1";
        $scope.KKasaKodu = "1";
        $scope.DepoNo = "1";
        $scope.FiyatListeNo = 1;
        $scope.PersonelKodu = 1;
        $scope.SorumlulukKodu = 1;
        $scope.EvrakTip = 1;
        //MENÜ
        $scope.PosSatis = true;
        $scope.StokListe = true;
        $scope.StokTanitim = true;
        $scope.CariListe = true;
        $scope.CariTanitim = true;

        $scope.PersonelListe = [];
        $scope.SorumlulukListe = [];
        $scope.KullaniciListe = [];
        $scope.DepoListe = [];
    }
    function InitKullaniciGrid()
    {   
        $("#TblKullanici").jsGrid({
            responsive: true,
            width: "100%",
            height: "500px",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.KullaniciListe,
            autoload: true,
            fields: 
            [
                {
                    name: "CODE",
                    title: "KODU",
                    type: "text",
                    align: "center",
                    width: 80
                },
                {
                    name: "NAME",
                    title: "KULLANICI",
                    type: "text",
                    align: "center",
                    width: 120
                },
                {
                    name: "PASSWORD",
                    title: "ŞİFRE",
                    type: "text",
                    align: "center",
                    width: 100
                }, 
                {
                    name: "YETKI",
                    title: "TAG",
                    type: "text",
                    align: "center",
                    width: 25
                },
                {
                    name: "DURUM",
                    title: "DURUM",
                    type: "number",
                    align: "center",
                    width: 25
                },
                [
                    { 
                        itemTemplate: function(_, item) 
                        {
                            return $("<button type='submit' style='height:30px; font-size: 12px;' class='btn btn-info btn-block'></button>").text("Güncelle")
                                .on("click", function() 
                                {
                                    $scope.BtnKullaniciGuncelle(0,item);
                                });
                        },
                        width: 25
                    }
                ],
                [
                    { 
                        itemTemplate: function(_, item) 
                        {
                            return $("<button type='submit' style='height:30px; font-size: 12px;' class='btn btn-danger btn-block'></button>").text("Sil")
                                .on("click", function() 
                                {
                                    alertify.okBtn('Evet');
                                    alertify.cancelBtn('Hayır');

                                    alertify.confirm('Kullanıcı Silmek İstediğinize Emin Misiniz ?', 
                                    function()
                                    { 
                                        KullaniciDelete(item);
                                    }
                                    ,function(){});
                                });
                        },
                        width: 25
                    }
                ],
                [
                    { 
                        itemTemplate: function(_, item) 
                        {
                            return $("<div class='btn-group'><button type='button' style='height:30px; font-size: 12px;' class='btn btn-primary dropdown-toggle' data-toggle='dropdown' aria-expanded='false'>Ayarlar</button><div class='dropdown-menu' aria-labelledby='exampleSizingDropdown1' role='menu'><a class='dropdown-item' role='menuitem' ng-click='Deneme()'>Sistem Ayarları</a><a class='dropdown-item' role='menuitem'>Pos Ayarları</a><a class='dropdown-item' role='menuitem'>Menü Ayarları</a></div></div>")
                                .on("click", function() 
                                {
                                    $scope.Kodu = item.CODE
                                });
                        },
                        width: 25
                    }
                ],
            ],
            rowClick: function(args)
            {   
                ParamGetir();
                if(args.event.target.outerText == 'Sistem Ayarları')
                {
                    $("#TbSistem").addClass('active');
                    $("#TbMain").removeClass('active');
                    $("#TbPosSatis").removeClass('active');
                    $("#TbMenu").removeClass('active');
                }
                else if(args.event.target.outerText == 'Pos Ayarları')
                {
                    $("#TbPosSatis").addClass('active');
                    $("#TbMain").removeClass('active');
                    $("#TbSistem").removeClass('active');
                    $("#TbMenu").removeClass('active');
                }
                else if(args.event.target.outerText == 'Menü Ayarları')
                {
                    $("#TbMenu").addClass('active');
                    $("#TbPosSatis").removeClass('active');
                    $("#TbSistem").removeClass('active');
                    $("#TbMain").removeClass('active');
                }
                $scope.$apply();
            },
        });
    }
    function KullaniciGetir()
    {
        Init();
        db.GetData($scope.Firma,'KullaniciGetir',[''],function(data)
        {   
            $scope.KullaniciListe = data;
            $("#TblKullanici").jsGrid({data : $scope.KullaniciListe}); 
        });
    }
    function KullaniciInsert()
    {
        var InsertData = 
        [
            $scope.Kodu,
            $scope.Kullanici,
            $scope.Sifre,
            $scope.Yetki,
            $scope.AktifPasif == true ? 1 : 0
        ];

        db.ExecuteTag($scope.Firma,'KullaniciInsert',InsertData,async function(InsertResult)
        {              
            if(typeof(InsertResult.result.err) == 'undefined')
            {   
                alert("Kayıt İşlemi Gerçekleşti.");
                //PARAM INSERT
                let Param =
                [
                    {
                        KiloBarkod : $scope.KiloBarkod,
                    },
                    {
                        KiloFlag : $scope.KiloFlag,
                    },
                    {
                        KiloBaslangic : $scope.KiloBaslangic,
                    },
                    {
                        KiloUzunluk : $scope.KiloUzunluk,
                    },
                    {
                        SatirBirlestir : $scope.SatirBirlestir,
                    },
                    {
                        SatisSeri : $scope.SatisSeri,
                    },
                    {
                        TahsilatSeri : $scope.TahsilatSeri,
                    },
                    {
                        IadeSeri : $scope.IadeSeri,
                    },
                    {
                        AvansSeri : $scope.AvansSeri,
                    },
                    {
                        CariKodu : $scope.CariKodu,
                    },
                    {
                        NKasaKodu : $scope.NKasaKodu,
                    },
                    {
                        KKasaKodu : $scope.KKasaKodu,
                    },
                    {
                        DepoNo : $scope.DepoNo,
                    },
                    {
                        FiyatListeNo : $scope.FiyatListeNo,
                    },
                    {
                        PersonelKodu : $scope.PersonelKodu,
                    },
                    {
                        SorumlulukKodu : $scope.SorumlulukKodu,
                    },
                    {
                        EvrakTip : $scope.EvrakTip,
                    },
                    {
                        PosSatis : $scope.PosSatis == true ? 1 : 0,
                    },
                    {
                        StokListe : $scope.StokListe == true ? 1 : 0,
                    },
                    {
                        StokTanitim : $scope.StokTanitim == true ? 1 : 0,
                    },
                    {
                        CariListe : $scope.CariListe == true ? 1 : 0,
                    },
                    {
                        CariTanitim : $scope.CariTanitim == true ? 1 : 0
                    },
                ]
                for (let i = 0; i < Param.length; i++) 
                {
                    let Tag = 0;
                    if(i <= 4)
                    {
                        Tag = 0;
                    }
                    else if(i <= 15)
                    {
                        Tag = 1;
                    }
                    else
                    {
                        Tag = 2;
                    }
                    ParamInsert(Object.keys(Param[i]),Object.values(Param[i]),Tag,$scope.Kodu)
                }
                $('#MdlKullanici').modal('hide');
                KullaniciGetir();
            }   
            else
            {
                alert("Kayıt İşleminde Hata.");
                console.log(InsertResult.result.err);
            }
        });
    }
    function KullaniciUpdate(pData)
    {
        db.ExecuteTag($scope.Firma,'KullaniciUpdate',pData,async function(InsertResult)
        {         
            if(typeof(InsertResult.result.err) == 'undefined')
            {   
                alert("Kullanıcı Güncellendi.");
                $('#MdlKullaniciGuncelle').modal('hide');
                KullaniciGetir();
            }   
            else
            {
                alert("Kullanıcı Güncelleme İşleminde Hata.");
                console.log(InsertResult.result.err);
            }
        });
    }
    function KullaniciDelete(pData)
    {
        db.ExecuteTag($scope.Firma,'KullaniciDelete',[pData.GUID],async function(InsertResult)
        {              
            if(typeof(InsertResult.result.err) == 'undefined')
            {   
                ParamDelete(pData);
                alert("Kullanıcı Silme İşlemi Gerçekleşti");
                KullaniciGetir();
            }   
            else
            {
                alert("Kullanıcı Silme İşleminde Hata.");
                console.log(InsertResult.result.err);
            }
        });
    }
    function ParamGetir()
    {
        db.GetData($scope.Firma,'ParamGetir',[$scope.Kodu],function(data)
        {   
            for (let i = 0; i < data.length; i++) 
            {
                //SİSTEM
                if(data[i].NAME == "KiloBarkod")
                {
                    $scope.KiloBarkod = data[i].VALUE;
                }
                else if(data[i].NAME == "KiloFlag")
                {
                    $scope.KiloFlag = data[i].VALUE;
                }
                else if(data[i].NAME == "KiloBaslangic")
                {
                    $scope.KiloBaslangic = data[i].VALUE;
                }
                else if(data[i].NAME == "KiloUzunluk")
                {
                    $scope.KiloUzunluk = data[i].VALUE;
                }
                else if(data[i].NAME == "SatirBirlestir")
                {
                    $scope.SatirBirlestir = data[i].VALUE;
                }
                //POSSATIŞ
                else if(data[i].NAME == "SatisSeri")
                {
                    $scope.SatisSeri = data[i].VALUE;
                }
                else if(data[i].NAME == "TahsilatSeri")
                {
                    $scope.TahsilatSeri = data[i].VALUE;
                }
                else if(data[i].NAME == "IadeSeri")
                {
                    $scope.IadeSeri = data[i].VALUE;
                }
                else if(data[i].NAME == "CariKodu")
                {
                    $scope.CariKodu = data[i].VALUE;
                }
                else if(data[i].NAME == "NKasaKodu")
                {
                    $scope.NKasaKodu = data[i].VALUE;
                }
                else if(data[i].NAME == "KKasaKodu")
                {
                    $scope.KKasaKodu = data[i].VALUE;
                }
                else if(data[i].NAME == "DepoNo")
                {
                    $scope.DepoNo = data[i].VALUE;
                }
                else if(data[i].NAME == "FiyatListeNo")
                {
                    $scope.FiyatListeNo = data[i].VALUE;
                }
                else if(data[i].NAME == "PersonelKodu")
                {
                    $scope.PersonelKodu = data[i].VALUE;
                }
                else if(data[i].NAME == "SorumlulukKodu")
                {
                    $scope.SorumlulukKodu = data[i].VALUE;
                }
                else if(data[i].NAME == "EvrakTip")
                {
                    $scope.EvrakTip = data[i].VALUE;
                }
                //MENÜ
                else if(data[i].NAME == "PosSatis")
                {
                    $scope.PosSatis = data[i].VALUE == 0 ? false : true;
                }
                else if(data[i].NAME == "StokListe")
                {
                    $scope.StokListe = data[i].VALUE == 0 ? false : true;
                }
                else if(data[i].NAME == "StokTanitim")
                {
                    $scope.StokTanitim = data[i].VALUE == 0 ? false : true;
                }
                else if(data[i].NAME == "CariListe")
                {
                    $scope.CariListe = data[i].VALUE == 0 ? false : true;
                }
                else if(data[i].NAME == "CariTanitim")
                {
                    $scope.CariTanitim = data[i].VALUE == 0 ? false : true;
                }
            }
            db.GetData($scope.Firma,'CmbDepoGetir',['TÜMÜ'],function(data)
            {   
                $scope.DepoListe = data;
            });
        });
    }
    function ParamDelete(pData)
    {
        db.ExecuteTag($scope.Firma,'ParamDelete',[pData.CODE],async function(InsertResult)
        {              
            if(typeof(InsertResult.result.err) == 'undefined')
            {   
             
            }   
            else
            {
                console.log(InsertResult.result.err);
            }
        });
    }
    function ParamInsert(pKeys,pValues,pTag,pKullanici)
    {
        let InsertData = 
        [
            pKullanici,
            pKullanici,
            pKeys[0],
            pValues[0],
            pTag,
            pKullanici
        ];

        db.ExecuteTag($scope.Firma,'ParamInsert',InsertData,async function(InsertResult)
        {              
            if(typeof(InsertResult.result.err) == 'undefined')
            {   
            }   
            else
            {
                console.log(InsertResult.result.err);
            }
        });
    }
    function ParamUpdate(pKeys,pValues,pKodu)
    {
        var UpdateData = 
        [
            pValues[0],
            pKeys[0],
            pKodu
        ];

        db.ExecuteTag($scope.Firma,'ParamUpdate',UpdateData,async function(UpdateResult)
        {              
            if(typeof(UpdateResult.result.err) == 'undefined')
            {   
                //alert("Parametre Güncellendi.");
            }   
            else
            {
                alert("Parametre Güncelleme İşleminde Hata.");
                console.log(UpdateResult.result.err);
            }
        });
    }
    $scope.KullaniciRowClick = function(pIndex,pItem,pObj)
    {
        if ( KullaniciListeRow ) { KullaniciListeRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = $("#TblKullanici").jsGrid("rowByItem", pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        KullaniciListeRow = $row;
    }
    $scope.BtnKullaniciInsert = function(pTip)
    {
        if(pTip == 0)
        {
            $("#MdlKullanici").modal("show");
            Init();
        }
        else
        {
            if($scope.Kodu != '' && $scope.Kullanici != '' && $scope.Sifre != '')
            {
                KullaniciInsert();
            }
            else
            {
                alertify.alert("Lütfen Boş Alanları Doldurun.");
            }
        }
    }
    $scope.BtnKullaniciGuncelle = function(pTip,pData)
    {
        if(pTip == 0)
        {
            $scope.Kodu = pData.CODE;
            $scope.Kullanici = pData.NAME;
            $scope.Sifre = pData.PASSWORD;
            $scope.AktifPasif = pData.STATUS == 0 ? false : true;
            $scope.KullaniciGuid = pData.GUID;
            $('#MdlKullaniciGuncelle').modal('show');
        }
        else
        {
            let UpdateData = 
            [
                $scope.Kodu,
                $scope.Kullanici,
                $scope.Sifre,
                $scope.AktifPasif == true ? 1 : 0,
                $scope.KullaniciGuid 
            ]

            KullaniciUpdate(UpdateData);
        }
    }
    $scope.BtnParamGuncelle = function()
    {
        if($scope.Kodu != "")
        {
            let Param =
            [
                {
                    KiloBarkod : $scope.KiloBarkod,
                },
                {
                    KiloFlag : $scope.KiloFlag,
                },
                {
                    KiloBaslangic : $scope.KiloBaslangic,
                },
                {
                    KiloUzunluk : $scope.KiloUzunluk,
                },
                {
                    SatirBirlestir : $scope.SatirBirlestir,
                },
                {
                    SatisSeri : $scope.SatisSeri,
                },
                {
                    TahsilatSeri : $scope.TahsilatSeri,
                },
                {
                    IadeSeri : $scope.IadeSeri,
                },
                {
                    AvansSeri : $scope.AvansSeri,
                },
                {
                    CariKodu : $scope.CariKodu,
                },
                {
                    NKasaKodu : $scope.NKasaKodu,
                },
                {
                    KKasaKodu : $scope.KKasaKodu,
                },
                {
                    DepoNo : $scope.DepoNo,
                },
                {
                    FiyatListeNo : $scope.FiyatListeNo,
                },
                {
                    PersonelKodu : $scope.PersonelKodu,
                },
                {
                    SorumlulukKodu : $scope.SorumlulukKodu,
                },
                {
                    EvrakTip : $scope.EvrakTip,
                },
                {
                    PosSatis : $scope.PosSatis == true ? 1 : 0,
                },
                {
                    StokListe : $scope.StokListe == true ? 1 : 0,
                },
                {
                    StokTanitim : $scope.StokTanitim == true ? 1 : 0,
                },
                {
                    CariListe : $scope.CariListe == true ? 1 : 0,
                },
                {
                    CariTanitim : $scope.CariTanitim == true ? 1 : 0
                },
            ]
            for (let i = 0; i < Param.length; i++) 
            {
                ParamUpdate(Object.keys(Param[i]),Object.values(Param[i]),$scope.Kodu)
            }
        }
        else
        {
            alert("Parametre Güncellemesi İçin Kullanıcı Seçmelisiniz.")
        }

        alert("Parametreler Güncellendi.");
    }
    $scope.YeniEvrak = function()
    {
        Init();
        InitKullaniciGrid();
        KullaniciGetir();

        db.GetData($scope.Firma,'CmbDepoGetir',['TÜMÜ'],function(data)
        {   
            $scope.DepoListe = data;
        });
    }
    $scope.KullaniciDepoChange = function()
    {
        KullaniciGetir();
    }
    $scope.BtnGeri = function()
    {
        $("#TbMain").addClass('active');
        $("#TbPosSatis").removeClass('active');
        $("#TbSistem").removeClass('active');
        $("#TbMenu").removeClass('active');
    }
}