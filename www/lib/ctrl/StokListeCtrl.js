function StokListeCtrl ($scope,$window,db)
{
    let GrdPage = true;
    let TmpFields =
    [
        {
            name: "CODE",
            title : "CODE",
            type : "text",
            align: "left",
            width: 100,
            itemTemplate: function(value) 
            {
                return $("<a>").attr("href", "#!Stok?Id=" + value).text(value);
            }            
        },
        {
            name: "NAME",
            title : "NAME",
            align: "left",
            width: 100
        },
        {
            name: "BARCODE",
            title : "BARCODE",
            align: "left",
            width: 75
        },
        {
            name: "SNAME",
            title : "SNAME",
            align: "left",
            width: 75,
            visible: false
        },
        {
            name: "ITEM_GRP",
            title : "ITEM GRP",
            align: "left",
            width: 75,
            visible: false
        },        
        {
            name: "VAT",
            title : "VAT",
            align: "center",
            width: 75,
            visible: false
        },
        {
            name: "COST_PRICE",
            title : "COST PRICE",
            align: "center",
            width: 75,
            visible: false
        },
        {
            name: "MIN_PRICE",
            title : "MIN PRICE",
            align: "center",
            width: 75,
            visible: false
        },
        {
            name: "MAX_PRICE",
            title : "MAX PRICE",
            align: "center",
            width: 75,
            visible: false
        },
        {
            name: "UNIT",
            title : "UNIT",
            align: "left",
            width: 75,
            visible: false
        },        
        {
            name: "PRICE",
            title : "PRICE",
            align: "center",
            width: 75,
            visible: false
        },
        {
            name: "CUSTOMER_ITEM_CODE",
            title : "CUSTOMER CODE",
            align: "left",
            width: 75,
            visible: false
        }
    ];
    let QueryField = 
    {
        Unit:
        {
            Field : "",
            Outer : ""
        },
        Price:
        {
            Field : "",
            Outer : ""
        },
        Customer:
        {
            Field : "",
            Outer : "",
            Where : ""
        },
        Barcode:
        {
            Field : "",
            Outer : "",
            Where : ""
        },
        Code:
        {
            Where : ""
        }
    }
    function TblStokInit()
    {
        $("#TblStok").jsGrid
        ({
            width: "100%",
            updateOnResize: true,
            heading: true,
            selecting: true,
            sorting: true,
            data : $scope.Data,
            paging : GrdPage,
            pageSize: 200,
            pageButtonCount: 5,
            pagerFormat: "{pages} {next} {last}    {pageIndex} of {pageCount}",
            fields: TmpFields
        });
    }
    function StokGetir()
    {
        QueryField.Unit.Field = "";
        QueryField.Unit.Outer = "";
        QueryField.Price.Field = "";
        QueryField.Price.Outer = "";
        QueryField.Customer.Field = "";
        QueryField.Customer.Outer = "";        
        QueryField.Customer.Where = "";
        QueryField.Barcode.Field = "";
        QueryField.Barcode.Outer = "";
        QueryField.Barcode.Where = "";
        QueryField.Code.Where = "";

        let TmpVal = ""
        
        for (let i = 0; i < $scope.Barkod.split(' ').length; i++) 
        {
            TmpVal += "'" + $scope.Barkod.split(' ')[i] + "'"
            if($scope.Barkod.split(' ').length > 1 && i !=  ($scope.Barkod.split(' ').length - 1))
            {
                TmpVal += ","
            }
        }

        for (let x = 0; x < $scope.Kolon.length; x++) 
        {
            
            if($scope.Kolon[x] == "UNIT")    
            {
                QueryField.Unit.Field = "ISNULL(ITEM_UNIT.NAME,'') AS UNIT, ";
                QueryField.Unit.Outer = "LEFT OUTER JOIN ITEM_UNIT ON ITEMS.CODE = ITEM_UNIT.ITEM_CODE ";
            } 
            if($scope.Kolon[x] == "PRICE")    
            {
                QueryField.Price.Field = "ISNULL(ITEM_PRICE.PRICE,0) AS PRICE, ";
                QueryField.Price.Outer = "LEFT OUTER JOIN ITEM_PRICE ON ITEM_PRICE.ITEM_CODE = ITEMS.CODE AND ITEM_PRICE.TYPE = 0 ";
            } 
            if($scope.Kolon[x] == "CUSTOMER_ITEM_CODE")    
            {
                QueryField.Customer.Field = "ISNULL(ITEM_CUSTOMER.CUSTOMER_ITEM_CODE,'') AS CUSTOMER_ITEM_CODE, ";
                QueryField.Customer.Outer = "LEFT OUTER JOIN ITEM_CUSTOMER ON ITEM_CUSTOMER.ITEM_CODE = ITEMS.CODE ";
                QueryField.Customer.Where = "OR ITEM_CUSTOMER.CUSTOMER_ITEM_CODE IN (" + TmpVal + ") "
            }   
            if($scope.Kolon[x] == "BARCODE")    
            {
                QueryField.Barcode.Field = "ISNULL(ITEM_BARCODE.BARCODE,'') AS BARCODE, ";
                QueryField.Barcode.Outer = "LEFT OUTER JOIN ITEM_BARCODE ON ITEM_BARCODE.ITEM_CODE = ITEMS.CODE ";

                if($scope.Barkod.split(' ').length > 1)
                {
                    QueryField.Barcode.Where = "ITEM_BARCODE.BARCODE IN (" + TmpVal + ") OR "
                }
                else
                {
                    QueryField.Barcode.Where = "ITEM_BARCODE.BARCODE LIKE " + TmpVal + " + '%' OR "
                }
            }  
        } 

        if($scope.Barkod.split(' ').length > 1)
        {
            QueryField.Code.Where = " ITEMS.CODE IN (" + TmpVal + ")) ";
        }
        else
        {
            QueryField.Code.Where = " ITEMS.CODE LIKE " + TmpVal + " + '%') ";
        }

        let TmpQuery = 
        {
            db : $scope.Firma,
            query:  "SELECT " +
                    "ITEMS.CODE AS CODE, " +
                    "ITEMS.NAME AS NAME, " +
                    "ITEMS.SNAME AS SNAME, " +
                    "ITEMS.ITEM_GRP AS ITEM_GRP, " +
                    "ITEMS.VAT AS VAT, " +
                    "ITEMS.COST_PRICE AS COST_PRICE, " +
                    "ITEMS.MIN_PRICE AS MIN_PRICE, " +
                    "ITEMS.MAX_PRICE AS MAX_PRICE, " +
                    QueryField.Unit.Field +
                    QueryField.Barcode.Field +
                    QueryField.Price.Field +
                    QueryField.Customer.Field +
                    "ITEMS.STATUS AS STATUS " +
                    "FROM ITEMS " +
                    QueryField.Unit.Outer +
                    QueryField.Barcode.Outer + 
                    QueryField.Price.Outer +
                    QueryField.Customer.Outer +
                    "WHERE ((" + QueryField.Barcode.Where + 
                    QueryField.Code.Where +
                    QueryField.Customer.Where + 
                    "OR (@BARCODE = '')) AND ((UPPER(ITEMS.NAME) LIKE UPPER(@NAME) + '%') OR (@NAME = '')) AND " +
                    "((ITEMS.ITEM_GRP = @ITEM_GRP) OR (@ITEM_GRP = '')) AND ITEMS.STATUS = @STATUS AND " +
                    "(((SELECT TOP 1 CUSTOMER_CODE FROM ITEM_CUSTOMER WHERE ITEM_CODE = ITEMS.CODE) = @CUSTOMER) OR (@CUSTOMER=''))",
            param : ["BARCODE:string|50","NAME:string|250","ITEM_GRP:string|25","STATUS:bit","CUSTOMER:string|25"],
            value : [$scope.Barkod,$scope.Adi,$scope.Grup,$scope.Durum,$scope.Tedarikci]
        }

        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.Data = Data
            $("#TblStok").jsGrid({data : $scope.Data});
        });
    }
    $scope.GrupGetir = function()
    {
        let TmpQuery = 
        {
            db : $scope.Firma,
            query:  "SELECT [NAME],[CODE] FROM ITEM_GROUP"
        }
        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.GrupList = Data
        });
    }
    $scope.TedarikciGetir = function()
    {
        let TmpQuery = 
        {
            db : $scope.Firma,
            query:  "SELECT CODE,NAME FROM CUSTOMERS WHERE TYPE = 1 ORDER BY NAME ASC"
        }
        db.GetDataQuery(TmpQuery,function(Data)
        {
            $scope.TedarikciList = Data
        });
    } 
    $scope.Init = function()
    {
        GrdPage = true;

        $scope.Data = [];
        $scope.GrupList = [];
        $scope.TedarikciList = [];

        $scope.Kolon = ["CODE","NAME","BARCODE"];
        $scope.Barkod = "";
        $scope.Adi = "";
        $scope.Grup = "";
        $scope.Tedarikci = "";
        $scope.Durum = true;

        TblStokInit();
        $scope.GrupGetir();
        $scope.TedarikciGetir();

        setTimeout(function () 
        {
            $('select').selectpicker('refresh');
        },500)
    }
    $scope.KolonChange = function()
    {
        for (let i = 0; i < TmpFields.length; i++) 
        {
            TmpFields[i].visible = false;
        }

        for (let i = 0; i < TmpFields.length; i++) 
        {
            for (let x = 0; x < $scope.Kolon.length; x++) 
            {
                if($scope.Kolon[x] == TmpFields[i].name)    
                {
                    TmpFields[i].visible = true;
                }                
            }            
        }

        TblStokInit();
    }
    $scope.BtnAra = function()
    {
        StokGetir();
    }
    $scope.TxtAra = function(keyEvent)
    {    
        if(keyEvent.which === 13)
        {   
            StokGetir();
        }
    }
    $scope.BtnAll = function()
    {
        GrdPage = false;
        TblStokInit();
    }
}