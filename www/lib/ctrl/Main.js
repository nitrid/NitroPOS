function Main ($scope,$rootScope,$window,db)
{
    function MenuOlustur()
    {   
        let HtmlText = "";
        
        $scope.User = "0";

        if($scope.User == "0")
        {
            HtmlText = HtmlText + "<a href='#!KullaniciParametre'>";
            HtmlText = HtmlText + "<i class='site-menu-icon wb-settings'></i>";
            HtmlText = HtmlText + "<span class='site-menu-title'>Ayarlar</span>";
            HtmlText = HtmlText + "<span class='site-menu-arrow'></span>";
            HtmlText = HtmlText + "</a>";
        }
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
        db.Connection(function(data)
        {
            MenuOlustur();
        });
    }
}