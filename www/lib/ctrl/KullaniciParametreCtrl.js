function KullaniciParametreCtrl($route,$scope,$window,$rootScope,db)
{
    let KullaniciListeRow = null;
    $('#MdlKullanici').on('hide.bs.modal', function () 
    {
        $scope.Kullanici = "";
        $scope.Kodu = "";
        $scope.Sifre = "";
        $scope.Yetki = "0";
        $scope.AktifPasif = true;
    });
    $('#MdlKullaniciGuncelle').on('hide.bs.modal', function () 
    {
        $scope.Kullanici = "";
        $scope.Kodu = "";
        $scope.Sifre = "";
        $scope.Yetki = "0";
        $scope.AktifPasif = true;
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
        $scope.Kullanici = "";
        $scope.Kodu = "";
        $scope.Sifre = "";
        $scope.Yetki = "0";
        $scope.AktifPasif = true;

        $scope.KullaniciListe = [];
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
                    title: "KULLANICI ID",
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
                                    $scope.$apply();
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
                                        $scope.$apply();
                                    }
                                    ,function(){});
                                });
                        },
                        width: 25
                    }
                ],
                [
                    // { 
                    //     itemTemplate: function(_, item) 
                    //     {
                    //         return $("<div class='btn-group'><button type='button' style='height:30px; font-size: 12px;' class='btn btn-primary dropdown-toggle' data-toggle='dropdown' aria-expanded='false'>Ayarlar</button><div class='dropdown-menu' aria-labelledby='exampleSizingDropdown1' role='menu'><a class='dropdown-item' role='menuitem' ng-click='Deneme()'>Sistem Ayarları</a><a class='dropdown-item' role='menuitem'>Pos Ayarları</a><a class='dropdown-item' role='menuitem'>Menü Ayarları</a></div></div>")
                    //             .on("click", function() 
                    //             {
                    //                 $scope.Kodu = item.CODE
                    //             });
                    //     },
                    //     width: 25
                    // }
                ],
            ],
        });
    }
    function KullaniciGetir()
    {
        db.GetData($scope.Firma,'KullaniciGetir',[''],function(data)
        {   
            $scope.KullaniciListe = data;
            $("#TblKullanici").jsGrid({data : $scope.KullaniciListe});
            $scope.BtnYeni();
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
                alertify.alert("Kayıt İşlemi Gerçekleşti.");
                $('#MdlKullanici').modal('hide');
                KullaniciGetir();
            }   
            else
            {
                alertify.alert("Kayıt İşleminde Hata.");
                console.log(InsertResult.result.err);
            }
        });
    }
    function KullaniciUpdate(pData)
    {
        console.log(pData)
        db.ExecuteTag($scope.Firma,'KullaniciUpdate',pData,async function(InsertResult)
        {         
            if(typeof(InsertResult.result.err) == 'undefined')
            {   
                alertify.alert("Kullanıcı Güncellendi.");
                $('#MdlKullaniciGuncelle').modal('hide');
                KullaniciGetir();
            }   
            else
            {
                alertify.alert("Kullanıcı Güncelleme İşleminde Hata.");
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
                alertify.alert("Kullanıcı Silme İşlemi Gerçekleşti");
                KullaniciGetir();
            }   
            else
            {
                alertify.alert("Kullanıcı Silme İşleminde Hata.");
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
            $scope.BtnYeni();
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
            $scope.Yetki = pData.TAG;
            $scope.AktifPasif = pData.STATUS == 0 ? false : true;
            $scope.KullaniciGuid = pData.GUID;
            $('#MdlKullaniciGuncelle').modal('show');
            console.log($scope.KullaniciGuid)
        }
        else
        {
            let UpdateData = 
            [
                $scope.Kodu,
                $scope.Kullanici,
                $scope.Yetki,
                $scope.Sifre,
                $scope.AktifPasif == true ? 1 : 0,
                $scope.KullaniciGuid 
            ]

            KullaniciUpdate(UpdateData);
        }
    }
    $scope.YeniEvrak = function()
    {
        Init();
        InitKullaniciGrid();
        KullaniciGetir();
    }
    $scope.BtnYeni = function()
    {
        $scope.Kullanici = "";
        $scope.Kodu = "";
        $scope.Sifre = "";
        $scope.Yetki = "0";
        $scope.AktifPasif = true;
    }
}