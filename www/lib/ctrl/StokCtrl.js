function StokCtrl ($scope,$window,$location,db)
{
    let UserParam = {};
    let SecimSelectedRow = null;
    let ModalTip = "";
    $scope.Birim =
    [
        {Kodu:"Unité",Symbol:"U"},
        {Kodu:"Kilogramme",Symbol:"KG"},
        {Kodu:"Colis",Symbol:"CO"},
        {Kodu:"Heure",Symbol:"H"},
        {Kodu:"Litre",Symbol:"L"},
        {Kodu:"Metre",Symbol:"M"},
        {Kodu:"Metre Carre",Symbol:"M2"},
        {Kodu:"Jour",Symbol:"J"}
    ];

    let DateField = function (config)
    {
        jsGrid.Field.call(this, config);
    };
    DateField.prototype = new jsGrid.Field(
    {
        sorter: function (date1, date2)
        {
            return new Date(date1) - new Date(date2);
        },
        itemTemplate: function (value,item)
        {
            if(item.TYPE != 0)
            {
                if (value.toLowerCase().indexOf("Date") == -1)
                {
                    return moment(new Date(value)).format("MM.DD.YYYY");
                }
                else
                {
                    return moment(new Date(value)).attr("style", "visibility: hidden")
                }
            }
        },
        insertTemplate: function (value)
        {
            return this._insertPicker = $("<input>").datepicker({
                format: 'dd.mm.yyyy'
            });
        },
        editTemplate: function (value,item)
        {
            if(item.TYPE != 0)
            {
                return this._editPicker = $("<input>").datepicker({
                    format: 'dd.mm.yyyy'
                }).datepicker("setDate", moment(new Date(value)).format("MM.DD.YYYY"));
            }
            
        },
        insertValue: function ()
        {
            return this._insertPicker.datepicker({
                format: 'dd.mm.yyyy'
            }).val();
        },
        editValue: function ()
        {
            if(this._editPicker != null)
            {
                return this._editPicker.datepicker({
                    format: 'dd.mm.yyyy'
                }).val();
            }
        }
    });
    jsGrid.fields.DateField = DateField;
    function TblFiyatInit()
    {
        $("#TblFiyat").jsGrid
        ({
            width: "100%",
            updateOnResize: true,
            heading: true,
            selecting: true,
            editing: true,
            data : $scope.FiyatListe,
            paging : true,
            pageSize: 5,
            pageButtonCount: 3,            
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields:
            [
                {
                    name: "TYPENAME",
                    title : "Tip",
                    align: "center",
                    width: 100

                },
                {
                    name: "DEPOT",
                    title : "Depo",
                    align: "center",
                    width: 100
                },
                {
                    name: "START_DATE",
                    title : "Baş.Tarih",
                    type: "DateField",
                    align: "center",
                    width: 75
                },
                {
                    name: "FINISH_DATE",
                    title : "Bit.Tarih",
                    type: "DateField",
                    align: "center",
                    width: 75
                },
                {
                    name: "QUANTITY",
                    title : "Miktar",
                    type: "decimal",
                    align: "center",
                    width: 75
                },
                {
                    name: "PRICE",
                    title : "Fiyat",
                    type: "decimal",
                    align: "center",
                    width: 75
                },
                {
                    name: "CUSTOMER",
                    title : "Cari",
                    align: "center",
                    width: 100
                },
                {
                    name: "EXVAT",
                    title : "VERGI HARIC",
                    align: "center",
                    width: 100
                },
                {
                    name: "BRUTMARJ",
                    title : "BRUT MARJ",
                    align: "center",
                    width: 100,
                    itemTemplate: function(value, item)
                    {
                        if(item.BRUTMARJORAN < 30)
                        {
                            return "<div style='color:red;font-weight: bold'>" + value + "</div>"
                        }
                        else
                        {
                            return "<div style='color:blue;font-weight: bold'>" + value + "</div>"
                        }
                    }
                },
                {
                    name: "NETMARJ",
                    title : "NET MARJ",
                    align: "center",
                    width: 100,
                    itemTemplate: function(value, item)
                    {
                        if(item.NETMARJORAN < 30)
                        {
                            return "<div style='color:red;font-weight: bold'>" + value + "</div>"
                        }
                        else
                        {
                            return "<div style='color:blue;font-weight: bold'>" + value + "</div>"
                        }
                    }
                },
                { type: "control", modeSwitchButton: true, editButton: false }
            ],
            confirmDeleting: false,
            onItemDeleting: function (args)
            {
                if (!args.item.deleteConfirmed)
                { // custom property for confirmation
                    args.cancel = true; // cancel deleting
                    alertify.okBtn('Evet');
                    alertify.cancelBtn('Hayır');

                    alertify.confirm('Fiyatı silmek istediğinize eminmisiniz ?',
                    function()
                    {
                        args.item.deleteConfirmed = true;
                        db.ExecuteTag($scope.Firma,'FiyatSil',[args.item.GUID],function(data)
                        {
                            //FİYAT LİSTESİ GETİR
                            db.GetData($scope.Firma,'StokKartFiyatListeGetir',[$scope.StokListe[0].CODE],function(FiyatData)
                            {
                                $scope.FiyatListe = FiyatData;
                                $("#TblFiyat").jsGrid({data : $scope.FiyatListe});
                                $scope.CmbAltBirimChange();
                            });
                        });
                    }
                    ,function(){});
                }
            },
            onItemUpdated: function(args)
            {
                db.ExecuteTag($scope.Firma,'FiyatUpdate',[args.item.PRICE,args.item.QUANTITY,args.item.START_DATE,args.item.FINISH_DATE,args.item.GUID],function(data)
                {
                    //FİYAT LİSTESİ GETİR
                    db.GetData($scope.Firma,'StokKartFiyatListeGetir',[$scope.StokListe[0].CODE],function(FiyatData)
                    {
                        $scope.FiyatListe = FiyatData;
                        $("#TblFiyat").jsGrid({data : $scope.FiyatListe});
                        $scope.CmbAltBirimChange();
                    });
                });
            }
        });
    }
    function TblBirimInit()
    {
        $("#TblBirim").jsGrid
        ({
            width: "100%",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.BirimListe,
            paging : true,
            pageSize: 5,
            pageButtonCount: 3,
            editing: true,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields:
            [
                {
                    name: "TYPENAME",
                    title : "Tip",
                    align: "center",
                    width: 100

                },
                {
                    name: "NAME",
                    title : "Adı",
                    align: "center",
                    width: 100
                },
                {
                    name: "FACTOR",
                    title : "Katsayı",
                    type: "number",
                    align: "center",
                    width: 75
                },
                {
                    name: "WEIGHT",
                    title : "Ağırlık",
                    type: "number",
                    align: "center",
                    width: 75
                },
                {
                    name: "VOLUME",
                    title : "Hacim",
                    type: "number",
                    align: "center",
                    width: 75
                },
                {
                    name: "WIDTH",
                    title : "En",
                    type: "number",
                    align: "center",
                    width: 100
                },
                {
                    name: "HEIGHT",
                    title : "Boy",
                    type: "number",
                    align: "center",
                    width: 100
                },
                {
                    name: "SIZE",
                    title : "Yükseklik",
                    type: "number",
                    align: "center",
                    width: 100
                },
                { type: "control", modeSwitchButton: true , editButton: false }
            ],
            confirmDeleting: false,
            onItemDeleting: function (args)
            {
                if (!args.item.deleteConfirmed)
                { // custom property for confirmation
                    args.cancel = true; // cancel deleting
                    alertify.okBtn('Evet');
                    alertify.cancelBtn('Hayır');

                    alertify.confirm('Birimi silmek istediğinize eminmisiniz ?',
                    function()
                    {
                        args.item.deleteConfirmed = true;
                        db.ExecuteTag($scope.Firma,'BirimSil',[args.item.GUID],function(data)
                        {
                            //BIRIM LİSTESİ GETİR
                            db.GetData($scope.Firma,'StokKartBirimListeGetir',[$scope.StokListe[0].CODE],function(BirimData)
                            {
                                $scope.BirimListe = BirimData;
                                $("#TblBirim").jsGrid({data : $scope.BirimListe});
                            });
                        });
                    }
                    ,function(){});
                }
            },
            onItemUpdated: function(args)
            {
                let TmpVal =
                [
                    args.item.FACTOR,
                    args.item.WEIGHT,
                    args.item.VOLUME,
                    args.item.WIDTH,
                    args.item.HEIGHT,
                    args.item.SIZE,
                    args.item.GUID
                ]
                db.ExecuteTag($scope.Firma,'BirimUpdate',TmpVal,function(data)
                {
                });
            }
        });
    }
    function TblBarkodInit()
    {
        $("#TblBarkod").jsGrid
        ({
            width: "100%",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.BarkodListe,
            paging : true,
            pageSize: 5,
            pageButtonCount: 3,
            editing: true,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields:
            [
                {
                    name: "BARCODE",
                    title : "Barkod",
                    type : "text",
                    align: "center",
                    width: 100

                },
                {
                    name: "UNIT",
                    title : "Birim",
                    align: "center",
                    width: 100
                },
                {
                    name: "TYPE",
                    title : "Tip",
                    align: "center",
                    width: 75
                },
                { type: "control", modeSwitchButton: true , editButton: false }
            ],
            confirmDeleting: false,
            onItemDeleting: function (args)
            {
                if (!args.item.deleteConfirmed)
                { // custom property for confirmation
                    args.cancel = true; // cancel deleting
                    alertify.okBtn('Evet');
                    alertify.cancelBtn('Hayır');

                    alertify.confirm('Barkod silmek istediğinize eminmisiniz ?',
                    function()
                    {
                        args.item.deleteConfirmed = true;
                        db.ExecuteTag($scope.Firma,'BarkodSil',[args.item.GUID],function(data)
                        {
                            //BARKOD LİSTESİ GETİR
                            db.GetData($scope.Firma,'StokKartBarkodListeGetir',[$scope.StokListe[0].CODE],function(BarkodData)
                            {
                                $scope.BarkodListe = BarkodData;
                                $("#TblBarkod").jsGrid({data : $scope.BarkodListe});
                            });
                        });
                    }
                    ,function(){});
                }
            },
            onItemUpdated: function(args)
            {
                let TmpVal =
                [
                    args.item.BARCODE,
                    args.item.GUID
                ]
                db.ExecuteTag($scope.Firma,'BarkodUpdate',TmpVal,function(data)
                {
                });
            }
        });
    }
    function TblTedarikciInit()
    {
        $("#TblTedarikci").jsGrid
        ({
            width: "100%",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.TedaikciListe,
            paging : true,
            pageSize: 5,
            pageButtonCount: 3,
            editing: true,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields:
            [
                {
                    name: "CUSTOMER_CODE",
                    title : "Kodu",
                    type : "text",
                    align: "center",
                    width: 100

                },
                {
                    name: "CUSTOMER_NAME",
                    title : "Adı",
                    align: "center",
                    width: 100
                },
                {
                    name: "PRICE_LDATE",
                    title : "Son Fiyat Tarih",
                    align: "center",
                    width: 100
                },
                {
                    name: "PRICE",
                    title : "Fiyat",
                    align: "center",
                    width: 100
                },
                {
                    name: "CUSTOMER_ITEM_CODE",
                    title : "Tedarikçi Stok Kodu",
                    type : "text",
                    align: "center",
                    width: 100
                },
                { type: "control", modeSwitchButton: true , editButton: false }
            ],
            confirmDeleting: false,
            onItemDeleting: function (args)
            {
                if (!args.item.deleteConfirmed)
                { // custom property for confirmation
                    args.cancel = true; // cancel deleting
                    alertify.okBtn('Evet');
                    alertify.cancelBtn('Hayır');

                    alertify.confirm('Tedarikçi silmek istediğinize eminmisiniz ?',
                    function()
                    {
                        args.item.deleteConfirmed = true;
                        db.ExecuteTag($scope.Firma,'StokTedarikciSil',[args.item.GUID],function(data)
                        {
                            //TEDARİKÇİ LİSTESİ GETİR
                            db.GetData($scope.Firma,'StokKartTedarikciListeGetir',[$scope.StokListe[0].CODE],function(TedarikciData)
                            {
                                $scope.TedaikciListe = TedarikciData;
                                $("#TblTedarikci").jsGrid({data : $scope.TedaikciListe});
                            });
                        });
                    }
                    ,function(){});
                }
            },
            onItemUpdated: function(args)
            {
                let TmpVal =
                [
                    args.item.CUSTOMER_CODE,
                    args.item.CUSTOMER_ITEM_CODE,
                    args.item.GUID
                ]
                db.ExecuteTag($scope.Firma,'StokTedarikciUpdate',TmpVal,function(data)
                {
                });
            }
        });
    }
    function TblTedarikciFiyatInit()
    {
        $("#TblTedarikciFiyat").jsGrid
        ({
            width: "100%",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : $scope.TedaikciFiyatListe,
            paging : true,
            pageSize: 10,
            pageButtonCount: 3,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields:
            [
                {
                    name: "CUSTOMER_CODE",
                    title : "Kodu",
                    type : "text",
                    align: "center",
                    width: 100

                },
                {
                    name: "CUSTOMER_NAME",
                    title : "Adı",
                    align: "center",
                    width: 100
                },
                {
                    name: "PRICE_LDATE",
                    title : "Son Fiyat Tarih",
                    align: "center",
                    width: 100
                },
                {
                    name: "PRICE",
                    title : "Fiyat",
                    align: "center",
                    width: 100
                },
                {
                    name: "CUSTOMER_ITEM_CODE",
                    title : "Tedarikçi Stok Kodu",
                    type : "text",
                    align: "center",
                    width: 100
                }
            ]
        });
    }
    function TblSecimInit(pData)
    {

        let TmpColumns = []

        if(pData.length > 0)
        {
            Object.keys(pData[0]).forEach(function(item)
            {
                TmpColumns.push({name : item,type: "text"});
            });
        }

        let db = {
            loadData: function(filter)
            {
                return $.grep(pData, function(client)
                {
                    return (!filter.CODE || client.CODE.toLowerCase().indexOf(filter.CODE.toLowerCase()) > -1)
                        && (!filter.NAME || client.NAME.toLowerCase().indexOf(filter.NAME.toLowerCase()) > -1)
                });
            }
        };

        $("#TblSecim").jsGrid
        ({
            width: "100%",
            updateOnResize: true,
            heading: true,
            selecting: true,
            data : pData,
            paging : true,
            filtering : true,
            pageSize: 15,
            pageButtonCount: 3,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields: TmpColumns,
            rowClick: function(args)
            {
                SecimListeRowClick(args.itemIndex,args.item,this);
                $scope.$apply();
            },
            controller:db,
        });
        $("#TblSecim").jsGrid("search");
    }
    function SecimListeRowClick(pIndex,pItem,pObj)
    {
        if ( SecimSelectedRow ) { SecimSelectedRow.children('.jsgrid-cell').css('background-color', '').css('color',''); }
        var $row = pObj.rowByItem(pItem);
        $row.children('.jsgrid-cell').css('background-color','#2979FF').css('color','white');
        SecimSelectedRow = $row;
        SecimSelectedRow.Item = pItem
        SecimSelectedRow.Index = pIndex

        $scope.BtnGridSec();
    }
    function FiyatModalInit()
    {
        $scope.FiyatModal = {};
        $scope.FiyatModal.Tip = "0";
        $scope.FiyatModal.StokKodu = $scope.StokListe[0].CODE;
        $scope.FiyatModal.Depo = "0";
        $scope.FiyatModal.Baslangic = moment(new Date()).format("DD.MM.YYYY");
        $scope.FiyatModal.Bitis = moment(new Date()).format("DD.MM.YYYY");
        $scope.FiyatModal.Fiyat = 0;
        $scope.FiyatModal.Miktar = 0;
        $scope.FiyatModal.Cari = "";
    }
    function BirimModalInit()
    {
        $scope.BirimModal = {};
        $scope.BirimModal.Tip = "0";
        $scope.BirimModal.Adi = "ADET";
        $scope.BirimModal.Katsayi = "0";
        $scope.BirimModal.Agirlik = "0";
        $scope.BirimModal.Hacim = "0";
        $scope.BirimModal.En = "0";
        $scope.BirimModal.Boy = "0";
        $scope.BirimModal.Yukseklik = "0";
    }
    function BarkodModalInit()
    {
        $scope.BarkodModal = {};
        $scope.BarkodModal.Barkod = "";
        $scope.BarkodModal.Birim = "0";
        $scope.BarkodModal.Tip = "0";
        $scope.BarkodModal.BirimListe = [];

        if($scope.BirimListe.length > 0)
        {
            $scope.BarkodModal.Birim = $scope.BirimListe[0].GUID;
            $scope.BarkodModal.BirimListe = $scope.BirimListe;
        }
    }
    function TedarikciModalInit()
    {
        $scope.TedarikciModal = {};
        $scope.TedarikciModal.Kodu = "";
        $scope.TedarikciModal.Adi = "";
        $scope.TedarikciModal.StokKodu = "";
    }
    function UrunGrupModalInit()
    {
        $scope.UrunGrupModal = {};
        $scope.UrunGrupModal.Kodu = "";
        $scope.UrunGrupModal.Adi = "";
    }
    function StokGetir(pKodu,pCallback)
    {
        db.GetData($scope.Firma,'StokKartGetir',[pKodu],function(StokData)
        {
            if(StokData.length > 0)
            {
                $scope.StyleAll = {'visibility': 'visible'};
                $scope.RefReadOnly = true;

                $scope.StokListe = [];
                $scope.StokListe = StokData;
                if($scope.StokListe[0].VAT == null)
                {
                    $scope.StokListe[0].VAT = "-"
                }
                //FİYAT LİSTESİ GETİR
                db.GetData($scope.Firma,'StokKartFiyatListeGetir',[pKodu],function(FiyatData)
                {
                    $scope.FiyatListe = FiyatData;
                    $("#TblFiyat").jsGrid({data : $scope.FiyatListe});

                    let TmpSymbol = "";
                    for(let i=0;i<$scope.Birim.length;i++)
                    {
                        if($scope.StokListe[0].UNDER_UNIT_NAME == $scope.Birim[i].Kodu)
                        {
                            TmpSymbol = $scope.Birim[i].Symbol;
                        }
                    }
                    if($scope.FiyatListe.length > 0)
                    {
                        $scope.AltBirimFiyati = ($scope.FiyatListe[0].PRICE / $scope.StokListe[0].UNDER_UNIT_FACTOR).toFixed(2) + "€ / " + TmpSymbol;
                    }
                });
                //BIRIM LİSTESİ GETİR
                db.GetData($scope.Firma,'StokKartBirimListeGetir',[pKodu],function(BirimData)
                {
                    $scope.BirimListe = BirimData;
                    $("#TblBirim").jsGrid({data : $scope.BirimListe});
                });
                //BARKOD LİSTESİ GETİR
                db.GetData($scope.Firma,'StokKartBarkodListeGetir',[pKodu],function(BarkodData)
                {
                    $scope.BarkodListe = BarkodData;
                    $("#TblBarkod").jsGrid({data : $scope.BarkodListe});
                });
                //TEDARİKÇİ LİSTESİ GETİR
                db.GetData($scope.Firma,'StokKartTedarikciListeGetir',[pKodu],function(TedarikciData)
                {
                    $scope.TedaikciListe = TedarikciData;
                    $("#TblTedarikci").jsGrid({data : $scope.TedaikciListe});

                    if($scope.TedaikciListe.length > 0)
                    {
                        $scope.StokListe[0].CUSTOMER_ITEM_CODE = TedarikciData[0].CUSTOMER_ITEM_CODE + ' / ' + TedarikciData[0].CUSTOMER_NAME;
                    }
                });
                //TEDARİKÇİ FİYAT LİSTESİ GETİR
                db.GetData($scope.Firma,'StokKartTedarikciFiyatListeGetir',[pKodu],function(TedarikciFiyatData)
                {
                    $scope.TedaikciFiyatListe = TedarikciFiyatData;
                    $("#TblTedarikciFiyat").jsGrid({data : $scope.TedaikciFiyatListe});
                });
            }

            if(typeof pCallback != 'undefined')
            {
                pCallback(StokData)
            }
        });
    }
    function BirimKaydet(pData,pCallback)
    {
        let InsertData = [];

        if(typeof pData == 'undefined')
        {
            InsertData =
            [
                UserParam.Kullanici,
                UserParam.Kullanici,
                $scope.StokListe[0].CODE,
                $scope.BirimModal.Tip,
                $scope.BirimModal.Adi,
                $scope.BirimModal.Katsayi,
                $scope.BirimModal.Agirlik,
                $scope.BirimModal.Hacim,
                $scope.BirimModal.En,
                $scope.BirimModal.Boy,
                $scope.BirimModal.Yukseklik
            ];
        }
        else
        {
            InsertData =
            [
                UserParam.Kullanici,
                UserParam.Kullanici,
                $scope.StokListe[0].CODE,
                pData[0],
                pData[1],
                pData[2],
                0,
                0,
                0,
                0,
                0
            ];
        }

        db.ExecuteTag($scope.Firma,'BirimKaydet',InsertData,function(InsertResult)
        {
            if(typeof pCallback != 'undefined')
            {
                pCallback(InsertResult.result.recordset[0].GUID);
            }

            if(typeof(InsertResult.result.err) == 'undefined')
            {
                //BIRIM LİSTESİ GETİR
                db.GetData($scope.Firma,'StokKartBirimListeGetir',[$scope.StokListe[0].CODE],function(BirimData)
                {
                    $scope.BirimListe = BirimData;
                    $("#TblBirim").jsGrid({data : $scope.BirimListe});

                    BarkodModalInit();
                });
            }
        });
    }
    $scope.Init = function(pClone)
    {
        UserParam = Param[$window.sessionStorage.getItem('User')];

        $scope.StyleAll = {'visibility': 'hidden'};
        $scope.RefReadOnly = false;

        $scope.AltBirimFiyati = "0.00 €";
        $scope.FiyatListe = [];
        $scope.BirimListe = [];
        $scope.BarkodListe = [];
        $scope.TedaikciListe = [];
        $scope.TedaikciListe = [];

        TblFiyatInit();
        TblBirimInit();
        TblBarkodInit();
        TblTedarikciInit();
        TblTedarikciFiyatInit();
        TblSecimInit([]);

        if(typeof pClone == 'undefined')
        {
            $scope.StokListe = [];

            let TmpStokObj = {};

            TmpStokObj.CODE = "";
            TmpStokObj.NAME = "";
            TmpStokObj.SNAME = "";
            TmpStokObj.ITEM_GRP = "";
            TmpStokObj.TYPE = "0";
            TmpStokObj.VAT = "-";
            TmpStokObj.STATUS = true;
            TmpStokObj.PLU = false;
            TmpStokObj.COST_PRICE = 0;
            TmpStokObj.MIN_PRICE = 0;
            TmpStokObj.MAX_PRICE = 0;
            TmpStokObj.UNDER_UNIT_NAME = "";
            TmpStokObj.UNDER_UNIT_FACTOR = 0;
            TmpStokObj.MAIN_UNIT_NAME = "Unité";
            TmpStokObj.MAIN_UNIT_FACTOR = 1;
            TmpStokObj.WEIGHING = false;
            TmpStokObj.BARCODE = "";

            $scope.StokListe.push(TmpStokObj);
        }
        else
        {
            $scope.StokListe[0].CODE = "";
            $scope.StokListe[0].BARCODE = "";
            $scope.StokListe[0].ITEM_CUSTOMER = "";
            $scope.StokListe[0].CUSTOMER_ITEM_CODE = "";
        }

        FiyatModalInit();
        BirimModalInit();
        BarkodModalInit();
        TedarikciModalInit();
        UrunGrupModalInit();

        if(typeof pClone == 'undefined')
        {
            if(typeof $location.$$search.Id != 'undefined')
            {
                StokGetir($location.$$search.Id);
            }
        }
    }
    $scope.Yeni = function()
    {
        window.location.href = "#!Stok";
    }
    $scope.Kaydet = function()
    {
        if($scope.StokListe[0].CODE == '')
        {
            alertify.okBtn("Tamam");
            alertify.alert("Kodu bölümünü boş geçemezsiniz !");
            return;
        }

        if($scope.StyleAll.visibility != 'hidden')
        {
            if($scope.StokListe[0].ITEM_CUSTOMER == "")
            {
                alertify.okBtn("Tamam");
                alertify.alert("Tedarikçi bölümünü boş geçemezsiniz !");
                return;
            }

            if($scope.StokListe[0].ITEM_GRP == "")
            {
                alertify.okBtn("Tamam");
                alertify.alert("Ürün grubu bölümünü boş geçemezsiniz !");
                return;
            }

            if($scope.StokListe[0].VAT == "-")
            {
                alertify.okBtn("Tamam");
                alertify.alert("Lütfen vergi dilimini seçiniz !");
                return;
            }

            if($scope.StokListe[0].UNDER_UNIT_FACTOR == 0)
            {
                alertify.okBtn("Tamam");
                alertify.alert("Lütfen alt birimi giriniz !");
                return;
            }
        }

        let InsertData =
        [
            UserParam.Kullanici,
            UserParam.Kullanici,
            $scope.StokListe[0].CODE,
            $scope.StokListe[0].NAME,
            $scope.StokListe[0].SNAME,
            $scope.StokListe[0].ITEM_GRP,
            $scope.StokListe[0].TYPE,
            $scope.StokListe[0].VAT,
            parseFloat($scope.StokListe[0].COST_PRICE.toString().replace(',','.')),
            parseFloat($scope.StokListe[0].MIN_PRICE.toString().replace(',','.')),
            parseFloat($scope.StokListe[0].MAX_PRICE.toString().replace(',','.')),
            $scope.StokListe[0].STATUS,
            $scope.StokListe[0].PLU,
            $scope.StokListe[0].WEIGHING
        ];

        db.ExecuteTag($scope.Firma,'StokKartKaydet',InsertData,function(InsertResult)
        {
            if(typeof(InsertResult.result.err) == 'undefined')
            {
                // ANA BİRİM KAYIT İŞLEMİ
                if($scope.StokListe[0].MAIN_UNIT_FACTOR > 0)
                {
                    let TmpVal = ["0",$scope.StokListe[0].MAIN_UNIT_NAME,parseFloat($scope.StokListe[0].MAIN_UNIT_FACTOR.toString().replace(',','.'))];
                    BirimKaydet(TmpVal,function(pGuid)
                    {
                        if($scope.StokListe[0].BARCODE != '')
                        {
                            $scope.BarkodModal.Barkod = $scope.StokListe[0].BARCODE
                            $scope.BarkodModal.Birim = pGuid
                            $scope.BarkodModal.Tip = 0

                            $scope.BtnBarkodKaydet();
                        }
                    });
                }

                // ALT BİRİM KAYIT İŞLEMİ
                if($scope.StokListe[0].UNDER_UNIT_FACTOR > 0)
                {
                    BirimKaydet(["1",$scope.StokListe[0].UNDER_UNIT_NAME,parseFloat($scope.StokListe[0].UNDER_UNIT_FACTOR.toString().replace(',','.'))]);
                }
            }

            //window.location.href = "#!Stok?Id=" + $scope.StokListe[0].CODE;
        });
    }
    $scope.Sil = function()
    {
        alertify.okBtn('Evet');
        alertify.cancelBtn('Hayır');

        alertify.confirm('Stoğu silmek istediğinize eminmisiniz ?',
        function()
        {
            if($scope.StokListe[0].CODE != '')
            {
                db.ExecuteTag($scope.Firma,'StokKartSil',[$scope.StokListe[0].CODE],function(data)
                {
                    $scope.Yeni();
                });
            }
            else
            {
                alertify.okBtn("Tamam");
                alertify.alert("Kayıtlı stok olmadan evrak silemezsiniz !");
            }
        }
        ,function(){});
    }
    $scope.Clone = function()
    {
        $scope.Init(true);
    }
    $scope.BtnFiyatKaydet = function()
    {
        $("#MdlFiyatEkle").modal('hide');

        if($scope.FiyatModal.StokKodu == "")
        {
            alertify.okBtn("Tamam");
            alertify.alert("Stok kodu bölümünü girmeden kayıt edemezsiniz !");
            return;
        }

        let InsertData =
        [
            UserParam.Kullanici,
            UserParam.Kullanici,
            $scope.FiyatModal.StokKodu,
            $scope.FiyatModal.Tip,
            $scope.FiyatModal.Depo,
            $scope.FiyatModal.Tip == "0" ? moment(new Date(0)).format("DD.MM.YYYY") : $scope.FiyatModal.Baslangic,
            $scope.FiyatModal.Tip == "0" ? moment(new Date(0)).format("DD.MM.YYYY") : $scope.FiyatModal.Bitis,
            parseFloat($scope.FiyatModal.Fiyat.toString().replace(',','.')),
            $scope.FiyatModal.Miktar,
            $scope.FiyatModal.Cari
        ];

        db.ExecuteTag($scope.Firma,'FiyatKaydet',InsertData,function(InsertResult)
        {
            if(typeof(InsertResult.result.err) == 'undefined')
            {
                //FİYAT LİSTESİ GETİR
                db.GetData($scope.Firma,'StokKartFiyatListeGetir',[$scope.StokListe[0].CODE],function(FiyatData)
                {
                    $scope.FiyatListe = FiyatData;
                    $("#TblFiyat").jsGrid({data : $scope.FiyatListe});
                    $scope.CmbAltBirimChange();
                });
            }
        });
    }
    $scope.BtnBirimKaydet = function()
    {
        $("#MdlBirimEkle").modal('hide');

        if($scope.BirimModal.Adi == "")
        {
            alertify.okBtn("Tamam");
            alertify.alert("Adı bölümünü girmeden kayıt edemezsiniz !");
            return;
        }

        BirimKaydet();
    }
    $scope.BtnBarkodKaydet = async function()
    {
        $("#MdlBarkodEkle").modal('hide');

        if($scope.BarkodModal.Barkod == "")
        {
            alertify.okBtn("Tamam");
            alertify.alert("Barkod bölümünü girmeden kayıt edemezsiniz !");
            return;
        }

        let TmpQuery =
        {
            db : $scope.Firma,
            query:  "SELECT [BARCODE] FROM ITEM_BARCODE WHERE [BARCODE] = @BARCODE AND [ITEM_CODE] <> @ITEM_CODE",
            param: ['BARCODE:string|50','ITEM_CODE:string|25'],
            value: [$scope.BarkodModal.Barkod,$scope.StokListe[0].CODE]
        }

        let TmpResult = await db.GetPromiseQuery(TmpQuery);

        if(TmpResult.length > 0)
        {
            alertify.okBtn("Tamam");
            alertify.alert("Girimiş olduğunuz barkod sistemde kayıtlı !");
            return;
        }

        let InsertData =
        [
            UserParam.Kullanici,
            UserParam.Kullanici,
            $scope.StokListe[0].CODE,
            $scope.BarkodModal.Barkod,
            $scope.BarkodModal.Birim,
            $scope.BarkodModal.Tip
        ];

        db.ExecuteTag($scope.Firma,'BarkodKaydet',InsertData,function(InsertResult)
        {
            if(typeof(InsertResult.result.err) == 'undefined')
            {
                //BARKOD LİSTESİ GETİR
                db.GetData($scope.Firma,'StokKartBarkodListeGetir',[$scope.StokListe[0].CODE],function(BarkodData)
                {
                    $scope.BarkodListe = BarkodData;
                    $scope.StokListe[0].BARCODE = $scope.BarkodModal.Barkod;
                    $("#TblBarkod").jsGrid({data : $scope.BarkodListe});
                });
            }
        });
    }
    $scope.BtnTedarikciKaydet = async function()
    {
        $("#MdlTedarikciEkle").modal('hide');

        if($scope.TedarikciModal.Kodu == "")
        {
            alertify.okBtn("Tamam");
            alertify.alert("Tedarikçi kodu bölümünü girmeden kayıt edemezsiniz !");
            return;
        }
        if($scope.StokListe[0].CODE == "")
        {
            alertify.okBtn("Tamam");
            alertify.alert("Stok kodu bölümünü girmeden kayıt edemezsiniz !");
            return;
        }
        let InsertData =
        [
            UserParam.Kullanici,
            UserParam.Kullanici,
            $scope.StokListe[0].CODE,
            $scope.TedarikciModal.Kodu,
            $scope.TedarikciModal.StokKodu
        ];

        let TmpQuery =
        {
            db : $scope.Firma,
            query:  "SELECT [CUSTOMER_ITEM_CODE],[ITEM_CODE] FROM ITEM_CUSTOMER WHERE [CUSTOMER_CODE] = @CUSTOMER_CODE AND [CUSTOMER_ITEM_CODE] = @CUSTOMER_ITEM_CODE",
            param: ['CUSTOMER_CODE:string|25','CUSTOMER_ITEM_CODE:string|25'],
            value: [$scope.TedarikciModal.Kodu,$scope.TedarikciModal.StokKodu]
        }

        let TmpResult = await db.GetPromiseQuery(TmpQuery);

        if(TmpResult.length > 0)
        {
            alertify.okBtn('Tamam');
            alertify.cancelBtn('Ürüne Git');
            alertify.confirm("Girimiş olduğunuz tedarikçi stok kodu sistemde kayıtlı",function()
            {
                $("#MdlTedarikciEkle").modal('show');
            },function()
            {
                StokGetir(TmpResult[0].ITEM_CODE);
            });
        }
        else
        {
            db.ExecuteTag($scope.Firma,'StokTedarikciKaydet',InsertData,function(InsertResult)
            {
                if(typeof(InsertResult.result.err) == 'undefined')
                {
                    //TEDARİKÇİ LİSTESİ GETİR
                    db.GetData($scope.Firma,'StokKartTedarikciListeGetir',[$scope.StokListe[0].CODE],function(TedarikciData)
                    {
                        $scope.TedaikciListe = TedarikciData;
                        $scope.StokListe[0].ITEM_CUSTOMER = $scope.TedarikciModal.Kodu;
                        $scope.StokListe[0].CUSTOMER_ITEM_CODE = $scope.TedarikciModal.StokKodu + ' / ' + $scope.TedarikciModal.Adi;
                        $("#TblTedarikci").jsGrid({data : $scope.TedaikciListe});
                    });
                }
            });
        }
    }
    $scope.BtnUrunGrupKaydet = function()
    {
        $("#MdlUrunGrupEkle").modal('hide');

        if($scope.UrunGrupModal.Kodu == "")
        {
            alertify.okBtn("Tamam");
            alertify.alert("Kodu bölümünü girmeden kayıt edemezsiniz !");
            return;
        }

        let InsertData =
        [
            UserParam.Kullanici,
            UserParam.Kullanici,
            $scope.UrunGrupModal.Kodu,
            $scope.UrunGrupModal.Adi
        ];

        db.ExecuteTag($scope.Firma,'UrunGrupKaydet',InsertData,function(InsertResult)
        {
            if(typeof(InsertResult.result.err) == 'undefined')
            {

            }
        });
    }
    $scope.BtnGridSec = function()
    {
        if(ModalTip == "Stok")
        {
            StokGetir(SecimSelectedRow.Item.CODE);
            $("#MdlSecim").modal('hide');
        }
        else if(ModalTip == "FiyatStok")
        {
            $scope.FiyatModal.StokKodu = SecimSelectedRow.Item.CODE;
            $("#MdlSecim").modal('hide');
            $("#MdlFiyatEkle").modal('show');
        }
        else if(ModalTip == "FiyatCari")
        {
            $scope.FiyatModal.Cari = SecimSelectedRow.Item.CODE;
            $("#MdlSecim").modal('hide');
            $("#MdlFiyatEkle").modal('show');
        }
        else if(ModalTip == "FiyatDepo")
        {
            $scope.FiyatModal.Depo = SecimSelectedRow.Item.CODE;
            $("#MdlSecim").modal('hide');
            $("#MdlFiyatEkle").modal('show');
        }
        else if(ModalTip == "TedarikciCari")
        {
            $scope.TedarikciModal.Kodu = SecimSelectedRow.Item.CODE;
            $scope.TedarikciModal.Adi = SecimSelectedRow.Item.NAME;
            $("#MdlSecim").modal('hide');
            $("#MdlTedarikciEkle").modal('show');
        }
        // else if(ModalTip == "TedarikciMaliyet")
        // {
        //     let InsertData =
        //     [
        //         UserParam.Kullanici,
        //         UserParam.Kullanici,
        //         $scope.StokListe[0].CODE,
        //         1,
        //         0,
        //         moment(new Date(0)).format("DD.MM.YYYY"),
        //         moment(new Date(0)).format("DD.MM.YYYY"),
        //         $scope.StokListe[0].COST_PRICE,
        //         SecimSelectedRow.Item.CODE
        //     ];

        //     db.ExecuteTag($scope.Firma,'FiyatKaydet',InsertData,function(InsertResult)
        //     {
        //         if(typeof(InsertResult.result.err) == 'undefined')
        //         {
        //             //FİYAT LİSTESİ GETİR
        //             db.GetData($scope.Firma,'StokKartFiyatListeGetir',[$scope.StokListe[0].CODE],function(FiyatData)
        //             {
        //                 $scope.FiyatListe = FiyatData;
        //                 $("#TblFiyat").jsGrid({data : $scope.FiyatListe});
        //             });
        //         }
        //     });

        //     $("#MdlSecim").modal('hide');
        // }
        else if(ModalTip == "UrunGrup")
        {
            $scope.StokListe[0].ITEM_GRP = SecimSelectedRow.Item.CODE;
            $("#MdlSecim").modal('hide');
        }
        ModalTip = "";
    }
    $scope.BtnModalKapat = function()
    {
        if(ModalTip == "Stok")
        {
            $("#MdlSecim").modal('hide');
        }
        else if(ModalTip == "FiyatStok")
        {
            $("#MdlSecim").modal('hide');
            $("#MdlFiyatEkle").modal('show');
        }
        else if(ModalTip == "FiyatCari")
        {
            $("#MdlSecim").modal('hide');
            $("#MdlFiyatEkle").modal('show');
        }
        else if(ModalTip == "FiyatDepo")
        {
            $("#MdlSecim").modal('hide');
            $("#MdlFiyatEkle").modal('show');
        }
        else if(ModalTip == "TedarikciCari")
        {
            $("#MdlSecim").modal('hide');
            $("#MdlTedarikciEkle").modal('show');
        }
        else if(ModalTip == "TedarikciMaliyet")
        {
            $("#MdlSecim").modal('hide');
        }
        else if(ModalTip == "UrunGrup")
        {
            $("#MdlSecim").modal('hide');
        }
        ModalTip = "";
    }
    $scope.BtnModalSecim = function(pTip)
    {
        ModalTip = pTip;

        if(ModalTip == "Stok")
        {
            let TmpQuery =
            {
                db : $scope.Firma,
                query:  "SELECT [CODE],[NAME] FROM ITEMS"
            }
            db.GetDataQuery(TmpQuery,function(Data)
            {
                TblSecimInit(Data);
                $("#MdlSecim").modal('show');
            });
        }
        else if(ModalTip == "FiyatStok")
        {
            let TmpQuery =
            {
                db : $scope.Firma,
                query:  "SELECT [CODE],[NAME] FROM ITEMS"
            }
            db.GetDataQuery(TmpQuery,function(Data)
            {
                TblSecimInit(Data);
                $("#MdlSecim").modal('show');
                $("#MdlFiyatEkle").modal('hide');
            });
        }
        else if(ModalTip == "FiyatCari")
        {
            let TmpQuery =
            {
                db : $scope.Firma,
                query:  "SELECT [CODE],[NAME] FROM CUSTOMERS"
            }
            db.GetDataQuery(TmpQuery,function(Data)
            {
                TblSecimInit(Data);
                $("#MdlSecim").modal('show');
                $("#MdlFiyatEkle").modal('hide');
            });
        }
        else if(ModalTip == "FiyatDepo")
        {
            let TmpQuery =
            {
                db : $scope.Firma,
                query:  "SELECT [CODE],[NAME] FROM DEPOT"
            }
            db.GetDataQuery(TmpQuery,function(Data)
            {
                TblSecimInit(Data);
                $("#MdlSecim").modal('show');
                $("#MdlFiyatEkle").modal('hide');
            });
        }
        else if(ModalTip == "TedarikciCari")
        {
            let TmpQuery =
            {
                db : $scope.Firma,
                query:  "SELECT [CODE],[NAME] FROM CUSTOMERS WHERE TYPE = 1"
            }
            db.GetDataQuery(TmpQuery,function(Data)
            {
                TblSecimInit(Data);
                $("#MdlSecim").modal('show');
                $("#MdlTedarikciEkle").modal('hide');
            });
        }
        // else if(ModalTip == "TedarikciMaliyet")
        // {
        //     let TmpQuery =
        //     {
        //         db : $scope.Firma,
        //         query:  "SELECT [CODE],[NAME] FROM CUSTOMERS"
        //     }
        //     db.GetDataQuery(TmpQuery,function(Data)
        //     {
        //         TblSecimInit(Data);
        //         $("#MdlSecim").modal('show');
        //         $("#MdlTedarikciEkle").modal('hide');
        //     });
        // }
        else if(ModalTip == "UrunGrup")
        {
            let TmpQuery =
            {
                db : $scope.Firma,
                query:  "SELECT [CODE],[NAME] FROM ITEM_GROUP"
            }
            db.GetDataQuery(TmpQuery,function(Data)
            {
                TblSecimInit(Data);
                $("#MdlSecim").modal('show');
            });
        }
    }
    $scope.BtnModalFiyatEkle = function()
    {
        if($scope.StokListe[0].CODE != "")
        {
            FiyatModalInit();
            $("#MdlFiyatEkle").modal('show');
        }
        else
        {
            alertify.okBtn("Tamam");
            alertify.alert("Kodu bölümünü girmeden fiyat giriş ekranına giremezsiniz !");
        }
    }
    $scope.BtnModalBirimEkle = function()
    {
        if($scope.StokListe[0].CODE != "")
        {
            BirimModalInit();
            $("#MdlBirimEkle").modal('show');
        }
        else
        {
            alertify.okBtn("Tamam");
            alertify.alert("Kodu bölümünü girmeden birim giriş ekranına giremezsiniz !");
        }
    }
    $scope.BtnModalBarkodEkle = function()
    {
        if($scope.StokListe[0].CODE != "" && $scope.BirimListe.length > 0)
        {
            BarkodModalInit();
            $("#MdlBarkodEkle").modal('show');
        }
        else
        {
            if($scope.StokListe[0].CODE == "")
            {
                alertify.okBtn("Tamam");
                alertify.alert("Kodu bölümünü girmeden barkod giriş ekranına giremezsiniz !");
            }
            else if($scope.BirimListe.length == 0)
            {
                alertify.okBtn("Tamam");
                alertify.alert("Birim bölümünü girmeden barkod giriş ekranına giremezsiniz !");
            }
        }
    }
    $scope.BtnModalTedarikciEkle = function()
    {
        TedarikciModalInit();
        $("#MdlTedarikciEkle").modal('show');
    }
    $scope.BtnModalUrunGrupEkle = function()
    {
        let TmpQuery =
            {
                db : $scope.Firma,
                query:  "SELECT (ISNULL(MAX(CODE),'') + 1) AS CODE FROM ITEM_GROUP"
            }
            db.GetDataQuery(TmpQuery,function(Data)
            {
                if(typeof Data[0].CODE != 'undefined')
                {
                    if(Data[0].CODE < 10)
                    {
                        $scope.UrunGrupModal.Kodu = ('00' +Data[0].CODE)
                    }
                    else if(Data[0].CODE < 100)
                    {
                        $scope.UrunGrupModal.Kodu = ('0' +Data[0].CODE)
                    }
                    else
                    {
                        $scope.UrunGrupModal.Kodu = Data[0].CODE
                    }
                }
                else
                {
                    $scope.UrunGrupModal.Kodu = '001'
                }
            });
        UrunGrupModalInit();
        $("#MdlUrunGrupEkle").modal('show');
    }
    $scope.CmbFiyatTipChange = function()
    {
        if($scope.FiyatModal.Tip == "0")
        {
            $("#BasTarih").prop('disabled',true);
            $("#BitTarih").prop('disabled',true);
        }
        else
        {
            $("#BasTarih").prop('disabled',false);
            $("#BitTarih").prop('disabled',false);
        }
    }
    $scope.TxtAdiChange = function()
    {
        $scope.StokListe[0].SNAME = $scope.StokListe[0].NAME.substring(0, 20);
    }
    $scope.BtnTabFiyat = function()
    {
        $("#TabFiyat").addClass('active');
        $("#TabBirim").removeClass('active');
        $("#TabBarkod").removeClass('active');
        $("#TabTedarikci").removeClass('active');
        $("#TabTedarikciFiyat").removeClass('active');
    }
    $scope.BtnTabBirim = function()
    {
        $("#TabBirim").addClass('active');
        $("#TabFiyat").removeClass('active');
        $("#TabBarkod").removeClass('active');
        $("#TabTedarikci").removeClass('active');
        $("#TabTedarikciFiyat").removeClass('active');
    }
    $scope.BtnTabBarkod = function()
    {
        $("#TabBarkod").addClass('active');
        $("#TabFiyat").removeClass('active');
        $("#TabBirim").removeClass('active');
        $("#TabTedarikci").removeClass('active');
        $("#TabTedarikciFiyat").removeClass('active');
    }
    $scope.BtnTabTedarikci = function()
    {
        $("#TabTedarikci").addClass('active');
        $("#TabFiyat").removeClass('active');
        $("#TabBarkod").removeClass('active');
        $("#TabBirim").removeClass('active');
        $("#TabTedarikciFiyat").removeClass('active');
    }
    $scope.BtnTabTedarikciFiyat = function()
    {
        $("#TabTedarikciFiyat").addClass('active');
        $("#TabTedarikci").removeClass('active');
        $("#TabFiyat").removeClass('active');
        $("#TabBarkod").removeClass('active');
        $("#TabBirim").removeClass('active');
    }
    $scope.TxtCostPriceValid = function()
    {
        var TmpQuery =
        {
            db : $scope.Firma,
            query:  "SELECT TOP 1 [PRICE] FROM ITEM_PRICE WHERE [ITEM_CODE] = '" + $scope.StokListe[0].CODE + "' AND [TYPE] = 1 ORDER BY LDATE DESC",
            param:  ['ITEM_CODE'],
            type:   ['strimg|25'],
            value:  [$scope.StokListe[0].CODE]
        }

        db.GetDataQuery(TmpQuery,function(Data)
        {
            if(Data.length == 0 || Data[0].PRICE != $scope.StokListe[0].COST_PRICE)
            {
                alertify.okBtn('Evet');
                alertify.cancelBtn('Hayır');

                alertify.confirm('Maliyet fiyatınıza tedarikçi bağlamak istermisiniz ?',
                function()
                {
                    let InsertData =
                    [
                        UserParam.Kullanici,
                        UserParam.Kullanici,
                        $scope.StokListe[0].CODE,
                        1,
                        0,
                        moment(new Date(0)).format("DD.MM.YYYY"),
                        moment(new Date(0)).format("DD.MM.YYYY"),
                        parseFloat($scope.StokListe[0].COST_PRICE.toString().replace(',','.')),
                        1,
                        $scope.StokListe[0].ITEM_CUSTOMER
                    ];

                    db.ExecuteTag($scope.Firma,'FiyatKaydet',InsertData,function(InsertResult)
                    {
                        if(typeof(InsertResult.result.err) == 'undefined')
                        {
                            //TEDARİKÇİ LİSTESİ GETİR
                            db.GetData($scope.Firma,'StokKartTedarikciListeGetir',[$scope.StokListe[0].CODE],function(TedarikciData)
                            {
                                $scope.TedaikciListe = TedarikciData;
                                $("#TblTedarikci").jsGrid({data : $scope.TedaikciListe});
                            });
                            //TEDARİKÇİ FİYAT LİSTESİ GETİR
                            db.GetData($scope.Firma,'StokKartTedarikciFiyatListeGetir',[pKodu],function(TedarikciFiyatData)
                            {
                                $scope.TedaikciFiyatListe = TedarikciFiyatData;
                                $("#TblTedarikciFiyat").jsGrid({data : $scope.TedaikciFiyatListe});
                            });
                        }
                    });

                    //$scope.BtnModalSecim('TedarikciMaliyet');
                }
                ,function()
                {
                });
            }
        });
    }
    $scope.CmbAnaBirimChange = function()
    {
        setTimeout( function()
        {
            $window.document.getElementById("TxtAnaBirim").focus();
            $window.document.getElementById("TxtAnaBirim").setSelectionRange(0, $window.document.getElementById("TxtAnaBirim").value.length);
        },100);
    }
    $scope.CmbAltBirimChange = function()
    {
        let TmpSymbol = "";
        let TmpFiyat = 0;

        for(let i = 0; i < $scope.Birim.length; i++)
        {
            if($scope.StokListe[0].UNDER_UNIT_NAME == $scope.Birim[i].Kodu)
            {
                TmpSymbol = $scope.Birim[i].Symbol;
            }
        }
        for (let i = 0; i < $scope.FiyatListe.length; i++)
        {
            if($scope.FiyatListe[i].TYPE == 0 && $scope.FiyatListe[i].QUANTITY == 1)
            {
                TmpFiyat = $scope.FiyatListe[i].PRICE;
            }
        }
        $scope.AltBirimFiyati = (TmpFiyat / $scope.StokListe[0].UNDER_UNIT_FACTOR).toFixed(2) + "€ / " + TmpSymbol;

        setTimeout( function(){
            $window.document.getElementById("TxtAltBirim").focus();
            $window.document.getElementById("TxtAltBirim").setSelectionRange(0, $window.document.getElementById("TxtAltBirim").value.length);
        },100);
    }
    $scope.TxtStokKeyPress = function(keyEvent)
    {
        if(typeof keyEvent == 'undefined')
        {
            StokGetir($scope.StokListe[0].CODE);
        }
        else
        {
            if(keyEvent.which === 13)
            {
                StokGetir($scope.StokListe[0].CODE);
            }
        }

    }
    $scope.TxtTedarikciKeyPress = function(keyEvent)
    {
        if(keyEvent.which === 13)
        {
            if($scope.StokListe[0].ITEM_CUSTOMER != "")
            {
                let TmpQuery =
                {
                    db : $scope.Firma,
                    query:  "SELECT [CODE],[NAME] FROM CUSTOMERS WHERE TYPE = 1 AND (CODE LIKE @CODE + '%' OR NAME LIKE @CODE + '%')",
                    param : ["CODE:string|100"],
                    value : [$scope.StokListe[0].ITEM_CUSTOMER]
                }
                db.GetDataQuery(TmpQuery,function(Data)
                {
                    if(Data.length == 1)
                    {
                        $scope.TedarikciModal.Kodu = Data[0].CODE;
                        $scope.TedarikciModal.Adi = Data[0].NAME;
                        $("#MdlSecim").modal('hide');
                        $("#MdlTedarikciEkle").modal('show');
                    }
                    else if(Data.length > 1)
                    {
                        ModalTip = "TedarikciCari"
                        TblSecimInit(Data);
                        $("#MdlSecim").modal('show');
                        $("#MdlTedarikciEkle").modal('hide');
                    }
                });
            }
        }
    }
    $scope.BtnKodOlustur = function()
    {
        if($scope.StyleAll.visibility == 'hidden')
        {
            $scope.StokListe[0].CODE = Math.floor(Date.now() / 1000);
        }
    }
    $scope.BtnRefKaydet = function()
    {
        if($scope.StyleAll.visibility == 'hidden')
        {
            StokGetir($scope.StokListe[0].CODE,function(pData)
            {
                if(pData.length == 0)
                {
                    $scope.Kaydet();
                }
            })
        }
    }
    $scope.TxtBarkodBlur = async function()
    {
        if($scope.StokListe[0].BARCODE != '')
        {
            let TmpQuery =
            {
                db : $scope.Firma,
                query:  "SELECT [BARCODE],[ITEM_CODE] FROM ITEM_BARCODE WHERE [BARCODE] = @BARCODE",
                param: ['BARCODE:string|50'],
                value: [$scope.StokListe[0].BARCODE]
            }

            let TmpResult = await db.GetPromiseQuery(TmpQuery);
            if(TmpResult.length > 0)
            {
                alertify.okBtn('Tamam');
                alertify.cancelBtn('Ürüne Git');
                alertify.confirm("Girimiş olduğunuz barkod sistemde kayıtlı",function()
                {
                    $scope.StokListe[0].BARCODE = "";
                },function()
                {
                    StokGetir(TmpResult[0].ITEM_CODE);
                });
            }
        }

    }
    $scope.CmbVatBlur = function()
    {
        if($scope.StokListe[0].VAT == "0")
        {
            alertify.okBtn("Tamam");
            alertify.alert("Vergi dilimi yuzde sıfır.Eminmisiniz ?");
            return;
        }
    }
    $scope.TxtUrunGrupKeyPress = function(keyEvent)
    {
        if(keyEvent.which === 13)
        {
            if($scope.StokListe[0].ITEM_GRP != "")
            {
                let TmpQuery =
                {
                    db : $scope.Firma,
                    query:  "SELECT [CODE],[NAME] FROM ITEM_GROUP WHERE CODE LIKE @CODE + '%'",
                    param : ["CODE:string|100"],
                    value : [$scope.StokListe[0].ITEM_GRP]
                }
                db.GetDataQuery(TmpQuery,function(Data)
                {
                    if(Data.length == 1)
                    {
                        $scope.StokListe[0].ITEM_GRP = Data[0].CODE;
                        $("#MdlSecim").modal('hide');
                    }
                    else if(Data.length > 1)
                    {
                        ModalTip = "UrunGrup"
                        TblSecimInit(Data);
                        $("#MdlSecim").modal('show');
                    }
                });
            }
        }
    }
}