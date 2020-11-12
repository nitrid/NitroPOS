function Main ($scope,$rootScope,$window,db)
{
    function MenuOlustur()
    {   
        let HtmlText = "";
       
        HtmlText = HtmlText + "<a>";
        HtmlText = HtmlText + "<i class='site-menu-icon wb-settings'></i>";
        HtmlText = HtmlText + "<span class='site-menu-title'>Ayarlar</span>";
        HtmlText = HtmlText + "<span class='site-menu-arrow'></span>";
        HtmlText = HtmlText + "</a>";
        HtmlText = HtmlText + "<ul class='site-menu-sub'>";
        HtmlText = HtmlText + "<li class='site-menu-item'>"
        HtmlText = HtmlText + "<a class='animsition-link' href='#!KullaniciParametre'>";
        HtmlText = HtmlText + "<span class='site-menu-title'>Kullanıcı Tanımlama</span>";
        HtmlText = HtmlText + "</a>";
        HtmlText = HtmlText + "</li>";
        HtmlText = HtmlText + "<li class='site-menu-item'>"
        HtmlText = HtmlText + "<a class='animsition-link' href='#!CihazParametre'>";
        HtmlText = HtmlText + "<span class='site-menu-title'>Cihaz Tanımlama</span>";
        HtmlText = HtmlText + "</a>";
        HtmlText = HtmlText + "</li>";
        HtmlText = HtmlText + "</ul>";
        $("#menu").html(HtmlText);     
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
    $scope.Init = function()
    {
        db.Connection(async function(data)
        {
            $scope.Kullanici = $window.sessionStorage.getItem('User');
            $scope.KullaniciListe = await db.GetPromiseTag($scope.Firma,'KullaniciGetir',[$scope.Kullanici]);

            let Yetkili = false;
            for (let i = 0; i < $scope.KullaniciListe.length; i++) 
            {
                if($scope.KullaniciListe[i].TAG == 1)
                {
                    Yetkili = true;
                }
            }

            if(Yetkili)
            MenuOlustur();
        });
    }
}