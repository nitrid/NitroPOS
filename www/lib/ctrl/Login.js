function Login ($scope,$rootScope,$window,db)
{
    localStorage.mode = true;

    $scope.server_adress = localStorage.host;
    $scope.socket_port = localStorage.socketport;
 
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
    $scope.Init = function()
    {
        $scope.Kullanici = "Admin";
        $scope.Password = 1;
        $scope.Firma = "NITROGENPOS";
        $scope.KullaniciListe = [];

        if (typeof localStorage.host == 'undefined')
        {
            localStorage.mode = "true";
            $scope.server_adress = window.location.hostname;
            $scope.socket_port = "";
            $scope.HostSettingSave();
        }
        db.Connection(function(data)
        {     
            if(data == true)
            {
                db.GetData($scope.Firma,'KullaniciGetir',[''],function(data)
                {   
                    $scope.KullaniciListe = data;
                });
            }



            // if(data == true)
            // {
            //     $('#alert').alert('close');
            // }
            // else
            // {
            //     $('#alert-box').html('<div class="alert alert-icon alert-danger alert-dismissible" role="alert" id="alert">' +
            //     '<button type="button" class="close" data-dismiss="alert" aria-label="Close">' +
            //     '<span aria-hidden="true">&times;</span>' +
            //     '</button>' +
            //     '<i class="icon wb-bell" aria-hidden="true"></i> Sunucuya erişim sağlanamadı.' +
            //     '<p class="mt-15">' +
            //     '<button class="btn btn-primary" data-target="#server-settings" data-toggle="modal"' +
            //     'type="button">Ayarlar</button></p></div>');
            //     db.Disconnect();
            // }
        });
    }
    $scope.HostSettingSave = function()
    {
        localStorage.host = $scope.server_adress;
        localStorage.socketport = $scope.socket_port;

        db.SetHost($scope.server_adress);
        $window.location.reload();
    }
    $scope.BtnEntry = function()
    {
        for(i = 0;i < $scope.KullaniciListe.length;i++)
        {
            if($scope.KullaniciListe[i].CODE == $scope.Kullanici && $scope.KullaniciListe[i].PASSWORD == $scope.Password)
            {
                console.log("Kullanıcı adı ve şifre doğru");
                $window.sessionStorage.setItem('User', $scope.Kullanici);
                
                var url = "pos.html";
                $window.location.href = url;
                return;
            }
        }
        alertify.okBtn("Tamam");
        alertify.alert("Kullanıcı adı veya şifre yanlış");
    }
    $scope.BtnTryConnect = function()
    {
        db.SetHost($scope.server_adress,$scope.socket_port);

        if(localStorage.mode == 'true')
        {
            db.Disconnect();
        }

        db.Connection(function(data)
        {
            if(data == true)
            {
                $scope.ConnectionStatus = 'Bağlantı Başarılı.';

                if(localStorage.mode == 'false')
                {
                    db.Disconnect();
                }
            }
            else
            {
                $scope.ConnectionStatus = 'Bağlantı Başarısız.';
                db.Disconnect();
            }
            $scope.$apply();            
        });
    }
}