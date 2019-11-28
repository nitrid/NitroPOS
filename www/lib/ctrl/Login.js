function Login ($scope,$rootScope,$window,db)
{
    let Firma = "TEST";
    let UserIndex = 0;

    $scope.server_adress = localStorage.host;
    $scope.server_port = localStorage.port;
    $scope.socket_port = localStorage.socketport;        
    $scope.IsDbCreateWorking = false;
    $scope.TransferEventProgress = 0;
    
    $scope.Init = function()
    {
        localStorage.mode = true;
        if (typeof localStorage.host == 'undefined')
        {
            db.SetHost($scope.server_adress,$scope.socket_port);
            //$window.location.reload();
        }
        
        db.SetHost($scope.server_adress,$scope.socket_port);

        if(localStorage.mode == 'true')
        {
            db.Connection(function(data)
            {                
                if(data == true)
                {
                    $('#alert').alert('close');
    
                    db.Emit('QMikroDb',QuerySql.Firma,(data) =>
                    {
                        if(typeof data.result.err == 'undefined')
                        {
                            $scope.Firm = Firma;
                            $scope.Kullanici = "";
                        }
                    });
                }
                else
                {
                    $('#alert-box').html('<div class="alert alert-icon alert-danger alert-dismissible" role="alert" id="alert">' +
                    '<button type="button" class="close" data-dismiss="alert" aria-label="Close">' +
                    '<span aria-hidden="true">&times;</span>' +
                    '</button>' +
                    '<i class="icon wb-bell" aria-hidden="true"></i> Sunucuya erişim sağlanamadı.' +
                    '<p class="mt-15">' +
                    '<button class="btn btn-primary" data-target="#server-settings" data-toggle="modal"' +
                    'type="button">Ayarlar</button></p></div>');
                    db.Disconnect();
                }
            });
        }
    }
    $scope.HostSettingSave = function()
    {
        localStorage.host = $scope.server_adress;
        localStorage.port = $scope.server_port;
        localStorage.socketport = $scope.socket_port;

        db.SetHost($scope.server_adress,$scope.socket_port);
        $window.location.reload();
    }
    $scope.BtnEntry = function()
    {
        for(i = 0;i < Param.length;i++)
        {
            if(Param[i].Kullanici == $scope.Kullanici && Param[i].Sifre == $scope.Password)
            {
                console.log("Kullanıcı adı ve şifre doğru");
                
                $window.sessionStorage.setItem('Firma', $scope.Firm);
                $window.sessionStorage.setItem('User', i);

                if(Param[i].SifreDegistir == "0")
                {
                    var url = "main.html";
                    $window.location.href = url;
                    return;
                }
                else
                {
                    UserIndex = i;
                    $("#MdlSifreDeg").modal("show"); 
                    return;
                }
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
    $scope.ChangeMode = function()
    {
        localStorage.mode = document.getElementById('inputBasicOn').checked;
        $window.location.reload();
    }
    $scope.BtnSifreKaydet = function()
    {
        let File = "./www/_pos/lib/Param.js";
        
        if($scope.EskiSifre != Param[UserIndex].Sifre)
        {
            alertify.alert("Eski Şifre Doğru Değil");
            return;
        }
        if($scope.YeniSifre1 == "" && $scope.YeniSifre2 == "")
        {
            alertify.alert("Yeni Şifrenizi Giriniz");
            return;
        }
        if($scope.YeniSifre1 != $scope.YeniSifre2)
        {
            alertify.alert("Yeni Girilen Şifreler Uyuşmuyor");
            return;
        }

        Param[UserIndex].Sifre = $scope.YeniSifre2;
        Param[UserIndex].SifreDegistir = "0";

        $scope.YeniSifre1 = "";
        $scope.YeniSifre2 = "";
        $scope.EskiSifre ="";
        db.Emit('ParamSave',[Param,File]);

        $window.location.reload();
    }
}