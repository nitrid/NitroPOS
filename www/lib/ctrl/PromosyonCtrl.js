function PromosyonCtrl($scope,$window,db)
{
    let CariSelectedRow = null;
    let StokSelectedRow = null;

    function Init()
    {
        UserParam = Param[$window.sessionStorage.getItem('User')];
        $scope.Kullanici = UserParam.Kullanici
        $scope.Firma = $window.sessionStorage.getItem('Firma');
        $scope.IlkTarih = moment(new Date()).format("DD.MM.YYYY");
        $scope.SonTarih = moment(new Date()).format("DD.MM.YYYY");
        
        $scope.CariKodu = "";
        $scope.CariAdi = "";
        $scope.StokKodu = "";
        $scope.StokAdi = "";
        $scope.TxtArama = "";
        $scope.PromosyonAdi = "";
        $scope.IndirimOran = 0;
        $scope.IndirimTutar = 0;
        $scope.SabitFiyat = 0 ;
        $scope.AnaGrup = "";
        
        $scope.ChkSube1 = true;
        $scope.ChkSube2 = true;
        $scope.ChkTekSeferlik = false;
        $scope.ChkDurum = true;
      
        $scope.CmbArama = "0";
        $scope.CariListe = [];
        $scope.StokListe = [];
        $scope.SubeListe = []
        $scope.AnaGrupListe = [];
        $scope.PromosyonListe = [];
        $scope.CmbSube = 
        {
            SubeListe : []
        };
    }
    function InitCariGrid()
    {   
        $("#TblCari").jsGrid
        ({
            width: "100%",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.CariListe,
            paging : true,
            pageSize: 10,
            pageButtonCount: 3,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields: 
            [
                {
                    name: "KODU",
                    type: "number",
                    align: "center",
                    width: 100
                    
                },
                {
                    name: "ADI",
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
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.StokListe,
            paging : true,
            pageSize: 10,
            pageButtonCount: 3,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields: 
            [
                {
                    name: "KODU",
                    type: "number",
                    align: "center",
                    width: 100
                },
                {
                    name: "ADI",
                    type: "text",
                    align: "center",
                    width: 300
                }
            ],
            rowClick: function(args)
            {
                $scope.StokListeRowClick(args.itemIndex,args.item,this);
                $scope.$apply();
            }
        });
    }
    function InitPromosyonGrid()
    {
        $("#TblPromosyon").jsGrid
        ({
            width: "100%",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.PromosyonListe,
            paging : true,
            pageSize: 10,
            pageButtonCount: 3,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields: 
            [
                {
                    name: "ADI",
                    type: "text",
                    align: "center",
                    width: 300
                },
                {
                    name: "OKULLANICI",
                    type: "text",
                    align: "center",
                    width: 150
                    
                },
                {
                    name: "BASTARIH",
                    type: "date",
                    align: "center",
                    width: 150
                    
                },
                {
                    name: "BITTARIH",
                    type: "date",
                    align: "center",
                    width: 150
                    
                },
                {
                    name: "CARI",
                    type: "text",
                    align: "center",
                    width: 150
                    
                },
                {
                    name: "INDORAN",
                    type: "number",
                    align: "center",
                    width: 150
                    
                },
                {
                    name: "INDTUTAR",
                    type: "number",
                    align: "center",
                    width: 150
                    
                },
                {
                    name: "SABITFIYAT",
                    type: "number",
                    align: "center",
                    width: 150
                },
                {
                    name: "DURUM",
                    type: "text",
                    align: "center",
                    width: 100
                },
               
            ],
            rowClick: function(args)
            {
                $scope.StokListeRowClick(args.itemIndex,args.item,this);
                $scope.$apply();
            }
        });
    }
    async function PromosyonInsert()
    {
        var InsertData = 
        [
            $scope.Kullanici,
            $scope.Kullanici,
            $scope.PromosyonAdi,
            $scope.CariKodu,    
            $scope.IlkTarih,
            $scope.SonTarih,
            $scope.IndirimOran,
            $scope.IndirimTutar,
            $scope.SabitFiyat,
            $scope.ChkTekSeferlik == true ? 1 : 0,
            $scope.ChkDurum == true ? 1 : 0 // DURUM
        ];
        db.ExecuteTag($scope.Firma,'PromosyonInsert',InsertData,async function(InsertResult)
        {   
            if(typeof(InsertResult) != 'undefined')
            {
                for (let i = 0; i < $scope.CmbSube.SubeListe.length; i++) 
                {
                    await PromosyonSubeInsert(InsertResult.result.recordset[0],$scope.CmbSube.SubeListe[i])
                }
                if($scope.AnaGrup != "" || $scope.StokKodu != "")
                {
                    if($scope.AnaGrup != "")
                    {
                        let StokData = await StokGetir($scope.AnaGrup);
                        for (let x = 0; x < StokData.length; x++) 
                        {
                            await PromosyonDetayInsert(InsertResult.result.recordset[0],StokData[x].KODU)
                        }
                    }
                    else
                    {
                        await PromosyonDetayInsert(InsertResult.result.recordset[0],$scope.StokKodu)
                    }
                }
            }
            else
            {
                console.log("Promosyon Kayıt İşleminde Hata")
            }

            alertify.alert("Promosyon Kayıt İşlemi Başarıyla Gerçekleşti.");
        });
    }
    function PromosyonSubeInsert(pData,pSube)
    {
        return new Promise(resolve =>
        {
            var InsertData = 
            [
                $scope.Kullanici,
                $scope.Kullanici,
                pSube,
                pData.UID
            ];
            db.ExecuteTag($scope.Firma,'PromosyonSubeInsert',InsertData,function(InsertResult)
            {   
                resolve(InsertResult)
            });
        });
    }
    function PromosyonDetayInsert(pData,pStok)
    {
        return new Promise(resolve =>
        {
            var InsertData = 
            [
                $scope.Kullanici,
                $scope.Kullanici,
                pStok,
                pData.UID
            ];
            db.ExecuteTag($scope.Firma,'PromosyonDetayInsert',InsertData,function(InsertResult)
            {   
                resolve(InsertResult)
            });
        });
    }
    function StokGetir(pAnaGrup)
    {
        return new Promise(resolve =>
        {
            db.GetData($scope.Firma,'StokListeGetir',['','',pAnaGrup],function(data)
            {
                resolve(data);
            });
        });
    }
    function PromosyonKontrol()
    {
        return new Promise(resolve =>
        {
            db.GetData($scope.Firma,'PromosyonKontrol',[$scope.CariKodu,$scope.CmbSube.SubeListe.toString(),$scope.StokKodu],function(data)
            {
                console.log(data)
                resolve(data);
            });
        });
    }
    $scope.YeniEvrak = function()
    {
        Init();
        InitCariGrid();
        InitStokGrid();
        InitPromosyonGrid();

        db.FillCmbDocInfo($scope.Firma,'CmbDepoGetir',function(data)
        {
            $scope.SubeListe = data;
            if($scope.SubeListe.length > 0)
            {
                setTimeout(function () 
                {
                    $('select').selectpicker('refresh');
                },500)
            }
        });
        db.FillCmbDocInfo($scope.Firma,'CmbAnaGrupGetir',function(data)
        {
            $scope.AnaGrupListe = data;
        });
    }
    $scope.BtnModalClick = function(pTip)
    {
        if(pTip == 0)
        {
            $('#MdlPromosyon').modal('show');
        }
        else if(pTip == 1)
        {
            $('#MdlMusteri').modal('show');
        }
        else if(pTip == 2)
        {
            $('#MdlStok').modal('show');
        }
    }
    $scope.BtnListeGetir = function(pTip)
    {
        let Kodu = '';
        let Adi = '';

        if($scope.TxtArama != "")
        {
            if($scope.CmbArama == "0")
            {   
                Adi = $scope.TxtArama.replace("*","%").replace("*","%");
            }
            else
            {
                Kodu = $scope.TxtArama.replace("*","%").replace("*","%");
            }
        }

        if(pTip == 0)
        {
            db.GetData($scope.Firma,'PromosyonGetir',[Adi],function(data)
            {
                console.log(data)
                $scope.PromosyonListe = data;
                console.log($scope.PromosyonListe)
                $("#TblPromosyon").jsGrid({data : $scope.PromosyonListe});
                $scope.TxtArama = '';
            });
        }
        else if(pTip == 1)
        {
            db.GetData($scope.Firma,'CariListeGetir',[Kodu,Adi],function(data)
            {
                $scope.CariListe = data;
                $("#TblCari").jsGrid({data : $scope.CariListe});
                $scope.TxtArama = '';
            });
        }
        else if(pTip == 2)
        {
            db.GetData($scope.Firma,'StokListeGetir',[Kodu,Adi,''],function(data)
            {
                $scope.StokListe = data;
                $("#TblStok").jsGrid({data : $scope.StokListe});
                $scope.TxtArama = '';
            });
        }
    }
    $scope.CariListeRowClick = function(pIndex,pItem,pObj)
    {
        if(!$scope.EvrakLock)
        {
            if ( CariSelectedRow ) { CariSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
            var $row = pObj.rowByItem(pItem);
            $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
            CariSelectedRow = $row;
            
            $scope.CariKodu = $scope.CariListe[pIndex].KODU;
            $scope.CariAdi = $scope.CariListe[pIndex].ADI;
        }
    }
    $scope.StokListeRowClick = function(pIndex,pItem,pObj)
    {
        if ( StokSelectedRow ) { StokSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = pObj.rowByItem(pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        StokSelectedRow = $row;
        
        $scope.StokKodu = $scope.StokListe[pIndex].KODU;
        $scope.StokAdi = $scope.StokListe[pIndex].KODU;
    }
    $scope.BtnKaydetClick = async function()
    {   
        let ProKontrol = await PromosyonKontrol();

        if($scope.CmbSube.SubeListe.length > 0)
        {
            console.log(ProKontrol[0].KONTROL)
            if(ProKontrol[0].KONTROL == '00000000-0000-0000-0000-000000000000')
            {
                PromosyonInsert();
            }
            else
            {
                alertify.alert("Seçtiğiniz Stoklara Ait Mevcutta Promosyon Bulunmakta.");
            }
        }
        else
        {
            alertify.alert("Lütfen Şube Seçimi Yapınız.");
        }
    }
}