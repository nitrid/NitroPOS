angular.module('app.controller', [])
.controller('Login',['$scope','$rootScope','$window','db',Login])
.controller('Main',['$scope','$rootScope','$window','db',Main])
.controller('KullaniciParametreCtrl',['$scope','$window','db',KullaniciParametreCtrl])
.controller('PosSatisCtrl',['$scope','$window','db',PosSatisCtrl])
.controller('SatisAktarimCtrl',['$scope','$window','db',SatisAktarimCtrl])
.controller('TahsilatAktarimCtrl',['$scope','$window','db',TahsilatAktarimCtrl])
.controller('RptGunlukSatisCtrl',['$scope','$window','db',RptGunlukSatisCtrl])
.controller('RptGunlukEvrakCtrl',['$scope','$window','db',RptGunlukEvrakCtrl])
.controller('RptGunlukKasaCtrl',['$scope','$window','db',RptGunlukKasaCtrl])
.controller('RptMagazaCiroCtrl',['$scope','$window','db',RptMagazaCiroCtrl])
.controller('RptMagazaSatisCtrl',['$scope','$window','db',RptMagazaSatisCtrl])
.controller('RptMagazaStokCtrl',['$scope','$window','db',RptMagazaStokCtrl])
.controller('RptDepoSatisHarCtrl',['$scope','$window','db',RptDepoSatisHarCtrl])
.controller('PluTanitimCtrl',['$scope','$window','db',PluTanitimCtrl])
.controller('SayimCtrl',['$scope','$window','$timeout','db',SayimCtrl])
.controller('AnaSayfaCtrl',['$scope','$window','db',AnaSayfaCtrl])

