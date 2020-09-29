function KullaniciParametreCtrl($route,$scope,$window,db)
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
    function Init()
    {
        UserParam = Param[$window.sessionStorage.getItem('User')];                
        $scope.Firma = 'NITROGENPOS'
        $scope.Kodu = "";
        $scope.Kullanici = "";
        $scope.Sifre = "";
        $scope.Yetki = "0";
        $scope.KullaniciGuid = "";
        $scope.AktifPasif = true;
        $scope.DepoNo = "TÜMÜ"

        $scope.KullaniciListe = [];
        $scope.DepoListe = [];
    }
    //KULLANICI EKRANI
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
                    width: 100
                },
                {
                    name: "NAME",
                    title: "KULLANICI",
                    type: "text",
                    align: "center",
                    width: 100
                },
                {
                    name: "PASSWORD",
                    title: "ŞİFRE",
                    type: "text",
                    align: "center",
                    width: 100
                }, 
                {
                    name: "TAG",
                    title: "TAG",
                    type: "text",
                    align: "center",
                    width: 25
                },
                {
                    name: "STATUS",
                    title: "STATUS",
                    type: "number",
                    align: "center",
                    width: 25
                },
                [
                    { 
                        itemTemplate: function(_, item) 
                        {
                            return $("<button type='submit' style='height:40px; font-size: 12px;' class='btn btn-info btn-block'></button>").text("Güncelle")
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
                            return $("<button type='submit' style='height:40px; font-size: 12px;' class='btn btn-danger btn-block'></button>").text("Sil")
                                .on("click", function() 
                                {
                                    KullaniciDelete(item);
                                });
                        },
                        width: 25
                    }
                ],
                [
                    { 
                        itemTemplate: function(_, item) 
                        {
                            return $("<div class='btn-group'><button type='button' style='height:40px; font-size: 12px;' class='btn btn-primary dropdown-toggle' data-toggle='dropdown' aria-expanded='false'>Ayarlar</button><div class='dropdown-menu' aria-labelledby='exampleSizingDropdown1' role='menu'><a class='dropdown-item' role='menuitem' ng-click='Deneme()'>Sistem Ayarları</a><a class='dropdown-item' role='menuitem'>Pos Ayarları</a><a class='dropdown-item' role='menuitem'>Menü Ayarları</a></div></div>")
                                .on("click", function() 
                                {
                                    
                                });
                        },
                        width: 25
                    }
                ],
                
            ],
            rowClick: function(args)
            {
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
        db.GetData($scope.Firma,'KullaniciGetir',[],function(data)
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
            $scope.Kodu = "";
            $scope.Kullanici = "";
            $scope.Sifre = "";
            $scope.Yetki = "0";
            $scope.AktifPasif = true;
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
            $scope.AktifPasif = true;
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

            KullaniciUpdate(UpdateData)
        }
    }
    $scope.YeniEvrak = function()
    {
        Init();
        InitKullaniciGrid();
        KullaniciGetir();

        db.GetData($scope.Firma,'CmbDepoGetir',[$scope.DepoNo],function(data)
        {   
            $scope.DepoListe = data;
        });
    }
    $scope.KullaniciDepoChange = function()
    {
        KullaniciGetir();
    }
}