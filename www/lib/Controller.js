angular.module('app.controller', [])
.controller('Login',['$scope','$rootScope','$window','db',Login])
.controller('Main',['$scope','$rootScope','$window','db',Main])
.controller('KullaniciParametreCtrl',['$route','$scope','$window','db',KullaniciParametreCtrl])
.controller('StokCtrl',['$scope','$window','$location','db',StokCtrl])
.controller('CariCtrl',['$scope','$window','$location','db',CariCtrl])
.controller('StokListeCtrl',['$scope','$window','db',StokListeCtrl])
.controller('CariListeCtrl',['$scope','$window','db',CariListeCtrl])