let Process = 
[
    {
        name: "STOK", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT sto_kod AS KODU,sto_isim AS ADI,'' AS KATEGORI,dbo.fn_VergiYuzde(sto_toptan_vergi) AS KDV,sto_anagrup_kod AS ANAGRUPKODU FROM STOKLAR"
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT KODU FROM STOKLAR WHERE KODU = @KODU",
            param:['KODU:string|25']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE STOKLAR SET ADI = @ADI, KATEGORI = @KATEGORI, KDV = @KDV, ANAGRUPKODU = @ANAGRUPKODU WHERE KODU = @KODU",
            param : ['KODU:string|25','ADI:string|150','KATEGORI:string|25','KDV:float','ANAGRUPKODU:string|25']
        },
        insert:     //INSERT SORGUSU
        {
            query : "INSERT INTO [dbo].[STOKLAR] " +
                    "([OKULLANICI] " +
                    ",[DKULLANICI] " +
                    ",[OTARIH] " +
                    ",[DTARIH] " +
                    ",[KODU] " +
                    ",[ADI] " +
                    ",[KATEGORI] " +
                    ",[KDV] " +
                    ",[ANAGRUPKODU] " +
                    ") VALUES ( " +
                    "'Admin'		--<OKULLANICI, nvarchar(10),> \n" +
                    ",'Admin'		--<DKULLANICI, nvarchar(10),> \n" +
                    ",GETDATE()		--<OTARIH, datetime,> \n" +
                    ",GETDATE()		--<DTARIH, datetime,> \n" +
                    ",@KODU			--<KODU, nvarchar(25),> \n" +
                    ",@ADI			--<ADI, nvarchar(150),> \n" +
                    ",@KATEGORI		--<KATEGORI, nvarchar(25),> \n" +
                    ",@KDV			--<KDV, float,> \n" +
                    ",@ANAGRUPKODU		--<ANAGRUPKODU, nvarchar(25),> \n" +
                    ")",
            param : ['KODU:string|25','ADI:string|150','KATEGORI:string|25','KDV:float','ANAGRUPKODU:string|25']
        }
    },
    {
        name: "CARI", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT cari_kod AS KODU,cari_unvan1 AS ADI ,cari_baglanti_tipi AS TIP FROM CARI_HESAPLAR"
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT KODU FROM CARILER WHERE KODU = @KODU",
            param:['KODU:string|25']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE CARILER SET ADI = @ADI,TIP = @TIP WHERE KODU = @KODU",
            param : ['KODU:string|25','ADI:string|150','TIP:int']
        },
        insert:     //INSERT SORGUSU
        {
            query : "INSERT INTO [dbo].[CARILER] " +
                    "([OKULLANICI] " +
                    ",[DKULLANICI] " +
                    ",[OTARIH] " +
                    ",[DTARIH] " +
                    ",[KODU] " +
                    ",[ADI] " +
                    ",[TIP] " +
                    ") VALUES ( " +
                    "'Admin'		--<OKULLANICI, nvarchar(10),> \n" +
                    ",'Admin'		--<DKULLANICI, nvarchar(10),> \n" +
                    ",GETDATE()		--<OTARIH, datetime,> \n" +
                    ",GETDATE()		--<DTARIH, datetime,> \n" +
                    ",@KODU			--<KODU, nvarchar(25),> \n" +
                    ",@ADI			--<ADI, nvarchar(150),> \n" +
                    ",@TIP			--<TIP, int,> \n" +
                    ")",
            param : ['KODU:string|25','ADI:string|150','TIP:int']
        }
    },
    {
        name: "BARKOD", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT bar_kodu AS KODU,bar_stokkodu AS STOK,bar_birimpntr AS BIRIM FROM BARKOD_TANIMLARI"
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT KODU FROM BARKODLAR WHERE KODU = @KODU",
            param:['KODU:string|25']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE BARKODLAR SET STOK = @STOK WHERE KODU = @KODU",
            param : ['KODU:string|25','STOK:string|25']
        },
        insert:     //INSERT SORGUSU
        {
            query : "INSERT INTO [dbo].[BARKODLAR] " +
                    "([OKULLANICI] " +
                    ",[DKULLANICI] " +
                    ",[OTARIH] " +
                    ",[DTARIH] " +
                    ",[KODU] " +
                    ",[STOK] " +
                    ",[BIRIM] " +
                    ") VALUES ( " +
                    "'Admin'		--<OKULLANICI, nvarchar(10),> \n" +
                    ",'Admin'		--<DKULLANICI, nvarchar(10),> \n" +
                    ",GETDATE()		--<OTARIH, datetime,> \n" +
                    ",GETDATE()		--<DTARIH, datetime,> \n" +
                    ",@KODU			--<KODU, nvarchar(25),> \n" +
                    ",@STOK			--<STOK, nvarchar(25),> \n" +
                    ",@BIRIM		--<BIRIM, nvarchar(10),> \n" +
                    ")",
            param : ['KODU:string|25','STOK:string|25','BIRIM:string|25']
        }
    },
    {
        name: "BIRIM", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT sto_kod AS STOK,sto_birimID AS KODU,sto_birim_ad AS ADI,CASE WHEN sto_birim_katsayi < 0 THEN sto_birim_katsayi * -1 ELSE sto_birim_katsayi END AS KATSAYI FROM STOK_BIRIM_TANIMLARI_DIKEY"
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT KODU FROM BIRIMLER WHERE KODU = @KODU AND STOK = @STOK",
            param:['KODU:string|10','STOK:string|25']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE BIRIMLER SET KATSAYI = @KATSAYI WHERE KODU = @KODU AND STOK = @STOK",
            param : ['KATSAYI:float','KODU:string|10','STOK:string|25']
        },
        insert:     //INSERT SORGUSU
        {
            query : "INSERT INTO [dbo].[BIRIMLER] " +
                    "([OKULLANICI] " +
                    ",[DKULLANICI] " +
                    ",[OTARIH] " +
                    ",[DTARIH] " +
                    ",[TIP] " +
                    ",[STOK] " +
                    ",[KODU] " +                    
                    ",[ADI] " +
                    ",[KATSAYI] " +
                    ") VALUES ( " +
                    "'Admin'		--<OKULLANICI, nvarchar(10),> \n" +
                    ",'Admin'		--<DKULLANICI, nvarchar(10),> \n" +
                    ",GETDATE()		--<OTARIH, datetime,> \n" +
                    ",GETDATE()		--<DTARIH, datetime,> \n" +
                    ",0 			--<TIP, smallint,> \n" +
                    ",@STOK			--<STOK, nvarchar(25),> \n" +
                    ",@KODU			--<KODU, nvarchar(10),> \n" +
                    ",@ADI		    --<ADI, nvarchar(25),> \n" +
                    ",@KATSAYI		--<KATSAYI, float,> \n" +
                    ")",
            param : ['STOK:string|25','KODU:string|10','ADI:string|25','KATSAYI:float']
        }
    },
    {
        name: "ALIŞ SİPARİŞİ", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT " + 
                  "CONVERT(nvarchar(10),sip_tarih,112) AS TARIH," + 
                  "sip_evrakno_seri AS SERI," + 
                  "sip_evrakno_sira AS SIRA," + 
                  "sip_satirno AS SATIRNO," + 
                  "sip_stok_kod AS KODU," + 
                  "CONVERT(nvarchar(25),sip_depono) AS GIRIS," + 
                  "sip_musteri_kod AS CIKIS," + 
                  "CONVERT(nvarchar(10),sip_birim_pntr) AS BIRIM," + 
                  "sip_miktar AS MIKTAR," + 
                  "sip_teslim_miktar AS TESLIM_MIKTAR," + 
                  "CONVERT(nvarchar(50),sip_Guid) AS OZEL, " +
                  "'' AS SATICI, " +
                  "'' AS TASIYICI, " +
                  "0 AS EMIRNO " + 
                  "FROM SIPARISLER WHERE sip_tip = 1 AND sip_cins IN( 0,3) AND sip_tarih >= GETDATE() - 60 " + 
                  "AND (SELECT TOP 1 sth_Guid FROM STOK_HAREKETLERI WHERE sth_sip_uid = sip_Guid) IS NULL"
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT OZEL FROM EMIRLER WHERE TIP = 0 AND CINS = 3 AND OZEL = @OZEL",
            param:['OZEL:string|50']
        },
        insert:     //INSERT SORGUSU
        {
            query : "INSERT INTO [dbo].[EMIRLER](" +
                    " [OKULLANICI]" +
                    ",[DKULLANICI]" +
                    ",[OTARIH]" +
                    ",[DTARIH]" +
                    ",[TIP]" +
                    ",[CINS]" +
                    ",[TARIH]" +
                    ",[SERI]" +
                    ",[SIRA]" +
                    ",[SATIRNO]" +
                    ",[KODU]" +
                    ",[GIRIS]" +
                    ",[CIKIS]" +
                    ",[BIRIM]" +
                    ",[MIKTAR]" +
                    ",[TESLIM_MIKTAR]" +
                    ",[OZEL]" +
                    ",[KAPALI]" +
                    ",[SATICI]" +
                    ",[TASIYICI]" +
                    ",[EMIRNO]" +
                    ",[DURUM]" +
                    ",[NOT]" +
                    ") VALUES ( " +
                    " 'Admin'						--<OKULLANICI, nvarchar(10),>\n" +
                    ",'Admin'						--<DKULLANICI, nvarchar(10),>\n" +
                    ",GETDATE()						--<OTARIH, datetime,>\n" +
                    ",GETDATE()						--<DTARIH, datetime,>\n" +
                    ",0 							--<TIP, smallint,>\n" +
                    ",3 							--<CINS, smallint,>\n" +
                    ",@TARIH						--<TARIH, datetime,>\n" +
                    ",@SERI							--<SERI, nvarchar(10),>\n" +
                    ",@SIRA							--<SIRA, int,>\n" +
                    ",@SATIRNO						--<SATIRNO, int,>\n" +
                    ",@KODU							--<KODU, nvarchar(25),>\n" +
                    ",@GIRIS						--<GIRIS, nvarchar(25),>\n" +
                    ",@CIKIS						--<CIKIS, nvarchar(25),>\n" +
                    ",@BIRIM						--<BIRIM, nvarchar(10),>\n" +
                    ",@MIKTAR						--<MIKTAR, float,>\n" +
                    ",@TESLIM_MIKTAR				--<TESLIM_MIKTAR, float,>\n" +
                    ",@OZEL							--<OZEL, nvarchar(50),>\n" +
                    ",0								--<KAPALI, smallint,>\n" +
                    ",@SATICI						--<SATICI, nvarchar(15),>\n" +
                    ",@TASIYICI						--<TASIYICI, nvarchar(15),>\n" +
                    ",@EMIRNO						--<EMIRNO, int,>\n" +
                    ",0						--<DURUM, int,>\n" +
                    ",''						--<NOT, nvarchar(50),>\n" +
                    ")",
            param : ['TARIH:string|10','SERI:string|10','SIRA:int','SATIRNO:int','KODU:string|25','GIRIS:string|25','CIKIS:string|25',
                     'BIRIM:string|10','MIKTAR:float','TESLIM_MIKTAR:float','OZEL:string|50','SATICI:string|15','TASIYICI:string|50',
                     'EMIRNO:int']
        }
    },
    {
        name: "SATIŞ SİPARİŞİ", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT " + 
                  "CONVERT(nvarchar(10),sip_tarih,112) AS TARIH," + 
                  "sip_evrakno_seri AS SERI," + 
                  "sip_evrakno_sira AS SIRA," + 
                  "sip_satirno AS SATIRNO," + 
                  "sip_stok_kod AS KODU," + 
                  "sip_musteri_kod AS GIRIS," + 
                  "CONVERT(nvarchar(25),sip_depono) AS CIKIS," + 
                  "CONVERT(nvarchar(10),sip_birim_pntr) AS BIRIM," + 
                  "sip_miktar AS MIKTAR," + 
                  "sip_teslim_miktar AS TESLIM_MIKTAR," + 
                  "CONVERT(nvarchar(50),sip_Guid) AS OZEL, " +
                  "sip_satici_kod AS SATICI, " +
                  "(SELECT dagitimci FROM CARI_HESAPLAR_USER WHERE Record_uid = (SELECT cari_Guid FROM CARI_HESAPLAR WHERE cari_kod = SIPARISLER.sip_musteri_kod)) AS TASIYICI, " +
                  "0 AS EMIRNO " +
                  "FROM SIPARISLER WHERE sip_tip = 0 AND sip_cins = 0 AND sip_tarih >= GETDATE() - 10 " + 
                  "AND (SELECT TOP 1 sth_Guid FROM STOK_HAREKETLERI WHERE sth_sip_uid = sip_Guid) IS NULL"
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT OZEL FROM EMIRLER WHERE TIP = 1 AND CINS = 3 AND OZEL = @OZEL",
            param:['OZEL:string|50']
        },
        insert:     //INSERT SORGUSU
        {
            query : "INSERT INTO [dbo].[EMIRLER](" +
                    " [OKULLANICI]" +
                    ",[DKULLANICI]" +
                    ",[OTARIH]" +
                    ",[DTARIH]" +
                    ",[TIP]" +
                    ",[CINS]" +
                    ",[TARIH]" +
                    ",[SERI]" +
                    ",[SIRA]" +
                    ",[SATIRNO]" +
                    ",[KODU]" +
                    ",[GIRIS]" +
                    ",[CIKIS]" +
                    ",[BIRIM]" +
                    ",[MIKTAR]" +
                    ",[TESLIM_MIKTAR]" +
                    ",[OZEL]" +
                    ",[KAPALI]" +
                    ",[SATICI]" +
                    ",[TASIYICI]" +
                    ",[EMIRNO]" +
                    ",[DURUM]" +
                    ",[NOT]" +
                    ") VALUES ( " +
                    " 'Admin'						--<OKULLANICI, nvarchar(10),>\n" +
                    ",'Admin'						--<DKULLANICI, nvarchar(10),>\n" +
                    ",GETDATE()						--<OTARIH, datetime,>\n" +
                    ",GETDATE()						--<DTARIH, datetime,>\n" +
                    ",1 							--<TIP, smallint,>\n" +
                    ",3 							--<CINS, smallint,>\n" +
                    ",@TARIH						--<TARIH, datetime,>\n" +
                    ",@SERI							--<SERI, nvarchar(10),>\n" +
                    ",@SIRA							--<SIRA, int,>\n" +
                    ",@SATIRNO						--<SATIRNO, int,>\n" +
                    ",@KODU							--<KODU, nvarchar(25),>\n" +
                    ",@GIRIS						--<GIRIS, nvarchar(25),>\n" +
                    ",@CIKIS						--<CIKIS, nvarchar(25),>\n" +
                    ",@BIRIM						--<BIRIM, nvarchar(10),>\n" +
                    ",@MIKTAR						--<MIKTAR, float,>\n" +
                    ",@TESLIM_MIKTAR				--<TESLIM_MIKTAR, float,>\n" +
                    ",@OZEL							--<OZEL, nvarchar(50),>\n" +
                    ",0								--<KAPALI, smallint,>\n" +
                    ",@SATICI						--<SATICI, nvarchar(15),>\n" +
                    ",@TASIYICI						--<TASIYICI, nvarchar(15),>\n" +
                    ",@EMIRNO						--<EMIRNO, int,>\n" +
                    ",0						--<DURUM, int,>\n" +
                    ",''						--<NOT, nvarchar(50),>\n" +
                    ")",
            param : ['TARIH:string|10','SERI:string|10','SIRA:int','SATIRNO:int','KODU:string|25','GIRIS:string|25','CIKIS:string|25',
                     'BIRIM:string|10','MIKTAR:float','TESLIM_MIKTAR:float','OZEL:string|50','SATICI:string|15','TASIYICI:string|50',
                     'EMIRNO:int']
        }
    },
    {
        name: "SİPARİŞ ALIŞ İRSALİYESİ", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT  " + 
                  "CONVERT(nvarchar(10),TARIH,112) AS TARIH, " + 
                  "SERI AS SERI, " + 
                  "SIRA AS SIRA, " + 
                  "SATIRNO AS SATIRNO, " + 
                  "STOK AS STOK, " + 
                  "PARTI AS PARTI," + 
                  "GIRIS AS GIRIS, " + 
                  "CIKIS AS CIKIS, " + 
                  "BIRIM AS BIRIM, " + 
                  "MIKTAR AS MIKTAR, " + 
                  "OZEL AS OZEL " + 
                  "FROM EMIR_HAREKETLERI WHERE TIP = 0 AND CINS = 3 AND DURUM = 1" 
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT sth_evrakno_seri,sth_evrakno_sira FROM STOK_HAREKETLERI WHERE sth_evrakno_seri = @SERI and sth_evrakno_sira = @SIRA AND sth_tip = 0 AND sth_evraktip = 13 AND sth_satirno =@SATIRNO ",
            param:['SERI:string|50','SIRA:int','SATIRNO:int']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE STOK_HAREKETLERI SET sth_miktar = @MIKTAR,sth_tutar = (SELECT sip_b_fiyat * @MIKTAR FROM SIPARISLER WHERE sip_Guid = @OZEL), " +
            " sth_iskonto1 = (SELECT sip_iskonto_1/sip_miktar * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) " +
            " WHERE sth_evraktip = 13 AND sth_evrakno_seri = @SERI AND sth_evrakno_sira = @SIRA AND sth_satirno = @SATIRNO" ,
            param : ['MIKTAR:float','OZEL:string|50','SERI:string|50','SIRA:int','SATIRNO:int']
        },
        insert : 
        {
            query : "DECLARE @UIDTABLE table([sth_Guid] [uniqueidentifier]) " +
                    "INSERT INTO [STOK_HAREKETLERI] " +
                    "([sth_DBCno] " +
                    ",[sth_SpecRECno] " +
                    ",[sth_iptal] " +
                    ",[sth_fileid] " +
                    ",[sth_hidden] " +
                    ",[sth_kilitli] " +
                    ",[sth_degisti] " +
                    ",[sth_checksum] " +
                    ",[sth_create_user] " +
                    ",[sth_create_date] " +
                    ",[sth_lastup_user] " +
                    ",[sth_lastup_date] " +
                    ",[sth_special1] " +
                    ",[sth_special2] " +
                    ",[sth_special3] " +
                    ",[sth_firmano] " +
                    ",[sth_subeno] " +
                    ",[sth_tarih] " +
                    ",[sth_tip] " +
                    ",[sth_cins] " +
                    ",[sth_normal_iade] " +
                    ",[sth_evraktip] " +
                    ",[sth_evrakno_seri] " +
                    ",[sth_evrakno_sira] " +
                    ",[sth_satirno] " +
                    ",[sth_belge_no] " +
                    ",[sth_belge_tarih] " +
                    ",[sth_stok_kod] " +
                    ",[sth_isk_mas1] " +
                    ",[sth_isk_mas2] " +
                    ",[sth_isk_mas3] " +
                    ",[sth_isk_mas4] " +
                    ",[sth_isk_mas5] " +
                    ",[sth_isk_mas6] " +
                    ",[sth_isk_mas7] " +
                    ",[sth_isk_mas8] " +
                    ",[sth_isk_mas9] " +
                    ",[sth_isk_mas10] " +
                    ",[sth_sat_iskmas1] " +
                    ",[sth_sat_iskmas2] " +
                    ",[sth_sat_iskmas3] " +
                    ",[sth_sat_iskmas4] " +
                    ",[sth_sat_iskmas5] " +
                    ",[sth_sat_iskmas6] " +
                    ",[sth_sat_iskmas7] " +
                    ",[sth_sat_iskmas8] " +
                    ",[sth_sat_iskmas9] " +
                    ",[sth_sat_iskmas10] " +
                    ",[sth_pos_satis] " +
                    ",[sth_promosyon_fl] " +
                    ",[sth_cari_cinsi] " +
                    ",[sth_cari_kodu] " +
                    ",[sth_cari_grup_no] " +
                    ",[sth_isemri_gider_kodu] " +
                    ",[sth_plasiyer_kodu] " +
                    ",[sth_har_doviz_cinsi] " +
                    ",[sth_har_doviz_kuru] " +
                    ",[sth_alt_doviz_kuru] " +
                    ",[sth_stok_doviz_cinsi] " +
                    ",[sth_stok_doviz_kuru] " +
                    ",[sth_miktar] " +
                    ",[sth_miktar2] " +
                    ",[sth_birim_pntr] " +
                    ",[sth_tutar] " +
                    ",[sth_iskonto1] " +
                    ",[sth_iskonto2] " +
                    ",[sth_iskonto3] " +
                    ",[sth_iskonto4] " +
                    ",[sth_iskonto5] " +
                    ",[sth_iskonto6] " +
                    ",[sth_masraf1] " +
                    ",[sth_masraf2] " +
                    ",[sth_masraf3] " +
                    ",[sth_masraf4] " +
                    ",[sth_vergi_pntr] " +
                    ",[sth_vergi] " +
                    ",[sth_masraf_vergi_pntr] " +
                    ",[sth_masraf_vergi] " +
                    ",[sth_netagirlik] " +
                    ",[sth_odeme_op] " +
                    ",[sth_aciklama] " +
                    ",[sth_sip_uid] " +
                    ",[sth_fat_uid] " +
                    ",[sth_giris_depo_no] " +
                    ",[sth_cikis_depo_no] " +
                    ",[sth_malkbl_sevk_tarihi] " +
                    ",[sth_cari_srm_merkezi] " +
                    ",[sth_stok_srm_merkezi] " +
                    ",[sth_fis_tarihi] " +
                    ",[sth_fis_sirano] " +
                    ",[sth_vergisiz_fl] " +
                    ",[sth_maliyet_ana] " +
                    ",[sth_maliyet_alternatif] " +
                    ",[sth_maliyet_orjinal] " +
                    ",[sth_adres_no] " +
                    ",[sth_parti_kodu] " +
                    ",[sth_lot_no] " +
                    ",[sth_kons_uid] " +
                    ",[sth_proje_kodu] " +
                    ",[sth_exim_kodu] " +
                    ",[sth_otv_pntr] " +
                    ",[sth_otv_vergi] " +
                    ",[sth_brutagirlik] " +
                    ",[sth_disticaret_turu] " +
                    ",[sth_otvtutari] " +
                    ",[sth_otvvergisiz_fl] " +
                    ",[sth_oiv_pntr] " +
                    ",[sth_oiv_vergi] " +
                    ",[sth_oivvergisiz_fl] " +
                    ",[sth_fiyat_liste_no] " +
                    ",[sth_oivtutari] " +
                    ",[sth_Tevkifat_turu] " +
                    ",[sth_nakliyedeposu] " +
                    ",[sth_nakliyedurumu] " +
                    ",[sth_yetkili_uid] " +
                    ",[sth_taxfree_fl] " +
                    ",[sth_ilave_edilecek_kdv] " + 
                    ",[sth_ismerkezi_kodu]  " +
                    ",[sth_HareketGrupKodu1] " +
                    ",[sth_HareketGrupKodu2] " +
                    ",[sth_HareketGrupKodu3]   " +
                    ",[sth_Olcu1]   " +
                    ",[sth_Olcu2]   " +
                    ",[sth_Olcu3]   " +
                    ",[sth_Olcu4]   " +
                    ",[sth_Olcu5]   " +
                    ",[sth_FormulMiktarNo]   " +
                    ",[sth_FormulMiktar]   " +
                    ") " +
                    "OUTPUT INSERTED.[sth_Guid] INTO @UIDTABLE " + 
                    "VALUES ( " +
                    "0					--<sth_DBCno, smallint,> \n" +
                    ",0					--<sth_SpecRECno, int,> \n" +
                    ",0	 				--<sth_iptal, bit,> \n" +
                    ",16					 --<sth_fileid, smallint,> \n" +
                    ",0		 			--<sth_hidden, bit,> \n" +
                    ",0		 			--<sth_kilitli, bit,> \n" +
                    ",0		 			--<sth_degisti, bit,> \n" +
                    ",0		 			--<sth_checksum, int,> \n" +
                    ",1 			--<sth_create_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_create_date, datetime,> \n" +
                    ",1			--<sth_lastup_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_lastup_date, datetime,> \n" +
                    ",''		 			--<sth_special1, varchar(4),> \n" +
                    ",''		 			--<sth_special2, varchar(4),> \n" +
                    ",''		 			--<sth_special3, varchar(4),> \n" +
                    ",0 			--<sth_firmano, int,> \n" +
                    ",0 			--<sth_subeno, int,> \n" +
                    ",@TARIH 				--<sth_tarih, datetime,> \n" +
                    ",0 				--<sth_tip, tinyint,> \n" +
                    ",(SELECT CASE sip_cins WHEN 0 THEN 0 WHEN 3 THEN 12 END FROM SIPARISLER WHERE sip_Guid =@OZEL) 				--<sth_cins, tinyint,> \n" +
                    ",0 			--<sth_normal_iade, tinyint,> \n" +
                    ",13 			--<sth_evraktip, tinyint,> \n" +
                    ",@SERI 			--<sth_evrakno_seri, varchar(4),> \n" +
                    ",@SIRA 			--<sth_evrakno_sira, int,> \n" +
                    ",@SATIRNO	--<sip_satirno, int,> \n" +
                    ",'' 			--sth_belge_no, varchar(15),> \n" +
                    ",GETDATE() 			--<sth_belge_tarih, datetime,> \n" +
                    ",@STOK 			--<sth_stok_kod, varchar(25),> \n" +
                    ",0		--<sth_isk_mas1, tinyint,> \n" +
                    ",0		--<sth_isk_mas2, tinyint,> \n" +
                    ",0		--<sth_isk_mas3, tinyint,> \n" +
                    ",0		--<sth_isk_mas4, tinyint,> \n" +
                    ",0		--<sth_isk_mas5, tinyint,> \n" +
                    ",0		--<sth_isk_mas6, tinyint,> \n" +
                    ",0		--<sth_isk_mas7, tinyint,> \n" +
                    ",0		--<sth_isk_mas8, tinyint,> \n" +
                    ",0		--<sth_isk_mas9, tinyint,> \n" +
                    ",0		--<sth_isk_mas10, tinyint,> \n" +
                    ",0			--<sth_sat_iskmas1, bit,> \n" +
                    ",0			--<sth_sat_iskmas2, bit,> \n" +
                    ",0			--<sth_sat_iskmas3, bit,> \n" +
                    ",0			--<sth_sat_iskmas4, bit,> \n" +
                    ",0			--<sth_sat_iskmas5, bit,> \n" +
                    ",0			--<sth_sat_iskmas6, bit,> \n" +
                    ",0			--<sth_sat_iskmas7, bit,> \n" +
                    ",0			--<sth_sat_iskmas8, bit,> \n" +
                    ",0			--<sth_sat_iskmas9, bit,> \n" +
                    ",0 			--<sth_sat_iskmas10, bit,> \n" +
                    ",0					--<sth_pos_satis, bit,> \n" +
                    ",0					--<sth_promosyon_fl, bit,> \n" +
                    ",0 			--<sth_cari_cinsi, tinyint,> \n" +
                    ",@CIKIS 			--<sth_cari_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_cari_grup_no, tinyint,> \n" +
                    ",''			 		--<sth_isemri_gider_kodu, varchar(25),> \n" +
                    ",''			--<sth_plasiyer_kodu, varchar(25),> \n" +
                    ",(SELECT sip_doviz_cinsi FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_har_doviz_cinsi, tinyint,> \n" +
                    ",(SELECT sip_doviz_kuru FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_har_doviz_kuru, float,> \n" +
                    ",(SELECT sip_alt_doviz_kuru FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_alt_doviz_kuru, float,> \n" +
                    ",(SELECT sip_doviz_cinsi FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_stok_doviz_cinsi, tinyint,> \n" +
                    ",(SELECT sip_doviz_kuru FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_stok_doviz_kuru, float,> \n" +
                    ",@MIKTAR 			--<sth_miktar, float,> \n" +
                    ",0 			--<sth_miktar2, float,> \n" +
                    ",1 			--<sth_birim_pntr, tinyint,> \n" +
                    ",(SELECT sip_b_fiyat * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL)	 			--<sth_tutar, float,> \n" +
                    ",(SELECT (sip_iskonto_1/sip_miktar) * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto1, float,> \n" +
                    ",(SELECT (sip_iskonto_2/sip_miktar)  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto2, float,> \n" +
                    ",(SELECT (sip_iskonto_3/sip_miktar)  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto3, float,> \n" +
                    ",(SELECT (sip_iskonto_4/sip_miktar)  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto4, float,> \n" +
                    ",(SELECT (sip_iskonto_5/sip_miktar)  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto5, float,> \n" +
                    ",(SELECT (sip_iskonto_6/sip_miktar)  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto6, float,> \n" +
                    ",0 			--<sth_masraf1, float,> \n" +
                    ",0 			--<sth_masraf2, float,> \n" +
                    ",0 			--<sth_masraf3, float,> \n" +
                    ",0 			--<sth_masraf4, float,> \n" +
                    ",(SELECT sip_vergi_pntr FROM SIPARISLER WHERE sip_Guid =@OZEL)			--<sth_vergi_pntr, tinyint,> \n" +
                    ",(SELECT (sip_vergi/sip_miktar) * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 				--<sth_vergi, float,> \n" +
                    ",(SELECT sip_masvergi_pntr FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_masraf_vergi_pntr, tinyint,> \n" +
                    ",(SELECT sip_masvergi FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_masraf_vergi, float,> \n" +
                    ",0		 			--<sth_netagirlik, float,> \n" +
                    ",0 			--<sth_odeme_op, int,> \n" +
                    ",(SELECT sip_aciklama  FROM SIPARISLER WHERE sip_Guid =@OZEL)  			--<sth_aciklama, varchar(50),> \n" +
                    ",@OZEL			 		--<sth_sip_uid, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier) 		--<sth_fat_uid, int,> \n" +
                    ",@GIRIS 			--<sth_giris_depo_no, int,> \n" +
                    ",@GIRIS 			--<sth_cikis_depo_no, int,> \n" +
                    ",GETDATE() 		--<sth_malkbl_sevk_tarihi, datetime,> \n" +
                    ",'' 		--<sth_cari_srm_merkezi, varchar(25),> \n" +
                    ",'' 		--<sth_stok_srm_merkezi, varchar(25),> \n" +
                    ",'18991230'	 			--<sth_fis_tarihi, datetime,> \n" +
                    ",0		 			--<sth_fis_sirano, int,> \n" +
                    ",(SELECT sip_vergisiz_fl FROM SIPARISLER WHERE sip_Guid =@OZEL) 		 			--<sth_vergisiz_fl, bit,> \n" +
                    ",0		 			--<sth_maliyet_ana, float,> \n" +
                    ",0			 		--<sth_maliyet_alternatif, float,> \n" +
                    ",0			 		--<sth_maliyet_orjinal, float,> \n" +
                    ",1 			--<sth_adres_no, int,> \n" +
                    ",@PARTI 			--<sth_parti_kodu, varchar(25),> \n" +
                    ",1	 			--<sth_lot_no, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)						--<sth_kons_uid, smallint,> \n" +
                    ",''		--<sth_proje_kodu, varchar(25),> \n" +
                    ",'' 			--<sth_exim_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_otv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_otv_vergi, float,> \n" +
                    ",0		 			--<sth_brutagirlik, float,> \n" +
                    ",1		--<sth_disticaret_turu, tinyint,> \n" +
                    ",0		 			--<sth_otvtutari, float,> \n" +
                    ",0			--<sth_otvvergisiz_fl, bit,> \n" +
                    ",0					--<sth_oiv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_oiv_vergi, float,> \n" +
                    ",0	 		--<sth_oivvergisiz_fl, bit,> \n" +
                    ",1 		--<sth_fiyat_liste_no, int,> \n" +
                    ",0			 		--<sth_oivtutari, float,> \n" +
                    ",0			 		--<sth_Tevkifat_turu, tinyint,> \n" +
                    ",0					--<sth_nakliyedeposu, int,> \n" +
                    ",0					--<sth_nakliyedurumu, tinyint,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)					--<sth_yetkili_uid, int,> \n" +
                    ",0					--<sth_taxfree_fl, bit,>  \n" +
                    ",0					--<sth_ilave_edilecek_kdv,float,> \n" +
                    ",''					--<sth_ismerkezi_kodu> \n" +
                    ",''					--<sth_HareketGrupKodu1, varchar(25),> \n" + 
                    ",''					--<sth_HareketGrupKodu2, varchar(25),>  \n" +
                    ",''					--<sth_HareketGrupKodu3, varchar(25),>  \n" +
                    ",0					--<sth_Olcu1, float,> \n" +
                    ",0					--<sth_Olcu2, float,> \n" +
                    ",0					--<sth_Olcu3, float,> \n" +
                    ",0					--<sth_Olcu4, float,> \n" +
                    ",0					--<sth_Olcu5, float,> \n" +
                    ",0					--<sth_FormulMiktarNo, tinyint,> \n" +
                    ",0					--<sth_FormulMiktar, float,> \n" +
                    ") " +
                    "SELECT [sth_Guid] FROM @UIDTABLE " +
                    "UPDATE SIPARISLER SET sip_teslim_miktar = sip_teslim_miktar + @MIKTAR WHERE sip_Guid = @OZEL ",
            param : ['TARIH:string|10','SERI:string|10','SIRA:int','STOK:string|25','CIKIS:string|25',
                    'MIKTAR:float','OZEL:string|50','GIRIS:int','PARTI:string|25','SATIRNO:int']
        },
    },
    {
        name: "YURT İÇİ ALIŞ İRSALİYESİ", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT  " + 
                  "CONVERT(nvarchar(10),TARIH,112) AS TARIH, " + 
                  "SERI AS SERI, " + 
                  "SIRA AS SIRA, " + 
                  "SATIRNO AS SATIRNO, " + 
                  "STOK AS STOK, " + 
                  "PARTI AS PARTI," + 
                  "GIRIS AS GIRIS, " + 
                  "CIKIS AS CIKIS, " + 
                  "BIRIM AS BIRIM, " + 
                  "MIKTAR AS MIKTAR, " + 
                  "CASE DURUM WHEN 11 THEN 0  WHEN 11 THEN 0 WHEN 12 THEN 12 END AS DURUM," +
                  "OZEL AS OZEL " + 
                  "FROM EMIR_HAREKETLERI WHERE TIP = 0 AND CINS = 3 AND DURUM = 11   " 
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT sth_evrakno_seri,sth_evrakno_sira FROM STOK_HAREKETLERI WHERE sth_evrakno_seri = @SERI and sth_evrakno_sira = @SIRA AND sth_tip = 0 AND sth_evraktip = 13 AND sth_satirno =@SATIRNO ",
            param:['SERI:string|50','SIRA:int','SATIRNO:int']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE STOK_HAREKETLERI SET sth_miktar = @MIKTAR " +
            " WHERE sth_evraktip = 13 AND sth_evrakno_seri = @SERI AND sth_evrakno_sira = @SIRA AND sth_satirno = @SATIRNO" ,
            param : ['MIKTAR:float','SERI:string|50','SIRA:int','SATIRNO:int']
        },
        
        insert : 
        {
            query : "DECLARE @UIDTABLE table([sth_Guid] [uniqueidentifier]) " +
                    "INSERT INTO [STOK_HAREKETLERI] " +
                    "([sth_DBCno] " +
                    ",[sth_SpecRECno] " +
                    ",[sth_iptal] " +
                    ",[sth_fileid] " +
                    ",[sth_hidden] " +
                    ",[sth_kilitli] " +
                    ",[sth_degisti] " +
                    ",[sth_checksum] " +
                    ",[sth_create_user] " +
                    ",[sth_create_date] " +
                    ",[sth_lastup_user] " +
                    ",[sth_lastup_date] " +
                    ",[sth_special1] " +
                    ",[sth_special2] " +
                    ",[sth_special3] " +
                    ",[sth_firmano] " +
                    ",[sth_subeno] " +
                    ",[sth_tarih] " +
                    ",[sth_tip] " +
                    ",[sth_cins] " +
                    ",[sth_normal_iade] " +
                    ",[sth_evraktip] " +
                    ",[sth_evrakno_seri] " +
                    ",[sth_evrakno_sira] " +
                    ",[sth_satirno] " +
                    ",[sth_belge_no] " +
                    ",[sth_belge_tarih] " +
                    ",[sth_stok_kod] " +
                    ",[sth_isk_mas1] " +
                    ",[sth_isk_mas2] " +
                    ",[sth_isk_mas3] " +
                    ",[sth_isk_mas4] " +
                    ",[sth_isk_mas5] " +
                    ",[sth_isk_mas6] " +
                    ",[sth_isk_mas7] " +
                    ",[sth_isk_mas8] " +
                    ",[sth_isk_mas9] " +
                    ",[sth_isk_mas10] " +
                    ",[sth_sat_iskmas1] " +
                    ",[sth_sat_iskmas2] " +
                    ",[sth_sat_iskmas3] " +
                    ",[sth_sat_iskmas4] " +
                    ",[sth_sat_iskmas5] " +
                    ",[sth_sat_iskmas6] " +
                    ",[sth_sat_iskmas7] " +
                    ",[sth_sat_iskmas8] " +
                    ",[sth_sat_iskmas9] " +
                    ",[sth_sat_iskmas10] " +
                    ",[sth_pos_satis] " +
                    ",[sth_promosyon_fl] " +
                    ",[sth_cari_cinsi] " +
                    ",[sth_cari_kodu] " +
                    ",[sth_cari_grup_no] " +
                    ",[sth_isemri_gider_kodu] " +
                    ",[sth_plasiyer_kodu] " +
                    ",[sth_har_doviz_cinsi] " +
                    ",[sth_har_doviz_kuru] " +
                    ",[sth_alt_doviz_kuru] " +
                    ",[sth_stok_doviz_cinsi] " +
                    ",[sth_stok_doviz_kuru] " +
                    ",[sth_miktar] " +
                    ",[sth_miktar2] " +
                    ",[sth_birim_pntr] " +
                    ",[sth_tutar] " +
                    ",[sth_iskonto1] " +
                    ",[sth_iskonto2] " +
                    ",[sth_iskonto3] " +
                    ",[sth_iskonto4] " +
                    ",[sth_iskonto5] " +
                    ",[sth_iskonto6] " +
                    ",[sth_masraf1] " +
                    ",[sth_masraf2] " +
                    ",[sth_masraf3] " +
                    ",[sth_masraf4] " +
                    ",[sth_vergi_pntr] " +
                    ",[sth_vergi] " +
                    ",[sth_masraf_vergi_pntr] " +
                    ",[sth_masraf_vergi] " +
                    ",[sth_netagirlik] " +
                    ",[sth_odeme_op] " +
                    ",[sth_aciklama] " +
                    ",[sth_sip_uid] " +
                    ",[sth_fat_uid] " +
                    ",[sth_giris_depo_no] " +
                    ",[sth_cikis_depo_no] " +
                    ",[sth_malkbl_sevk_tarihi] " +
                    ",[sth_cari_srm_merkezi] " +
                    ",[sth_stok_srm_merkezi] " +
                    ",[sth_fis_tarihi] " +
                    ",[sth_fis_sirano] " +
                    ",[sth_vergisiz_fl] " +
                    ",[sth_maliyet_ana] " +
                    ",[sth_maliyet_alternatif] " +
                    ",[sth_maliyet_orjinal] " +
                    ",[sth_adres_no] " +
                    ",[sth_parti_kodu] " +
                    ",[sth_lot_no] " +
                    ",[sth_kons_uid] " +
                    ",[sth_proje_kodu] " +
                    ",[sth_exim_kodu] " +
                    ",[sth_otv_pntr] " +
                    ",[sth_otv_vergi] " +
                    ",[sth_brutagirlik] " +
                    ",[sth_disticaret_turu] " +
                    ",[sth_otvtutari] " +
                    ",[sth_otvvergisiz_fl] " +
                    ",[sth_oiv_pntr] " +
                    ",[sth_oiv_vergi] " +
                    ",[sth_oivvergisiz_fl] " +
                    ",[sth_fiyat_liste_no] " +
                    ",[sth_oivtutari] " +
                    ",[sth_Tevkifat_turu] " +
                    ",[sth_nakliyedeposu] " +
                    ",[sth_nakliyedurumu] " +
                    ",[sth_yetkili_uid] " +
                    ",[sth_taxfree_fl] " +
                    ",[sth_ilave_edilecek_kdv] " + 
                    ",[sth_ismerkezi_kodu]  " +
                    ",[sth_HareketGrupKodu1] " +
                    ",[sth_HareketGrupKodu2] " +
                    ",[sth_HareketGrupKodu3]   " +
                    ",[sth_Olcu1]   " +
                    ",[sth_Olcu2]   " +
                    ",[sth_Olcu3]   " +
                    ",[sth_Olcu4]   " +
                    ",[sth_Olcu5]   " +
                    ",[sth_FormulMiktarNo]   " +
                    ",[sth_FormulMiktar]   " +
                    ") " +
                    "OUTPUT INSERTED.[sth_Guid] INTO @UIDTABLE " + 
                    "VALUES ( " +
                    "0					--<sth_DBCno, smallint,> \n" +
                    ",0					--<sth_SpecRECno, int,> \n" +
                    ",0	 				--<sth_iptal, bit,> \n" +
                    ",16					 --<sth_fileid, smallint,> \n" +
                    ",0		 			--<sth_hidden, bit,> \n" +
                    ",0		 			--<sth_kilitli, bit,> \n" +
                    ",0		 			--<sth_degisti, bit,> \n" +
                    ",0		 			--<sth_checksum, int,> \n" +
                    ",1 			--<sth_create_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_create_date, datetime,> \n" +
                    ",1			--<sth_lastup_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_lastup_date, datetime,> \n" +
                    ",''		 			--<sth_special1, varchar(4),> \n" +
                    ",''		 			--<sth_special2, varchar(4),> \n" +
                    ",''		 			--<sth_special3, varchar(4),> \n" +
                    ",0 			--<sth_firmano, int,> \n" +
                    ",0 			--<sth_subeno, int,> \n" +
                    ",@TARIH 				--<sth_tarih, datetime,> \n" +
                    ",0 				--<sth_tip, tinyint,> \n" +
                    ",@DURUM				--<sth_cins, tinyint,> \n" +
                    ",0 			--<sth_normal_iade, tinyint,> \n" +
                    ",13 			--<sth_evraktip, tinyint,> \n" +
                    ",@SERI 			--<sth_evrakno_seri, varchar(4),> \n" +
                    ",@SIRA 			--<sth_evrakno_sira, int,> \n" +
                    ",@SATIRNO	--<sip_satirno, int,> \n" +
                    ",'' 			--sth_belge_no, varchar(15),> \n" +
                    ",GETDATE() 			--<sth_belge_tarih, datetime,> \n" +
                    ",@STOK 			--<sth_stok_kod, varchar(25),> \n" +
                    ",0		--<sth_isk_mas1, tinyint,> \n" +
                    ",0		--<sth_isk_mas2, tinyint,> \n" +
                    ",0		--<sth_isk_mas3, tinyint,> \n" +
                    ",0		--<sth_isk_mas4, tinyint,> \n" +
                    ",0		--<sth_isk_mas5, tinyint,> \n" +
                    ",0		--<sth_isk_mas6, tinyint,> \n" +
                    ",0		--<sth_isk_mas7, tinyint,> \n" +
                    ",0		--<sth_isk_mas8, tinyint,> \n" +
                    ",0		--<sth_isk_mas9, tinyint,> \n" +
                    ",0		--<sth_isk_mas10, tinyint,> \n" +
                    ",0			--<sth_sat_iskmas1, bit,> \n" +
                    ",0			--<sth_sat_iskmas2, bit,> \n" +
                    ",0			--<sth_sat_iskmas3, bit,> \n" +
                    ",0			--<sth_sat_iskmas4, bit,> \n" +
                    ",0			--<sth_sat_iskmas5, bit,> \n" +
                    ",0			--<sth_sat_iskmas6, bit,> \n" +
                    ",0			--<sth_sat_iskmas7, bit,> \n" +
                    ",0			--<sth_sat_iskmas8, bit,> \n" +
                    ",0			--<sth_sat_iskmas9, bit,> \n" +
                    ",0 			--<sth_sat_iskmas10, bit,> \n" +
                    ",0					--<sth_pos_satis, bit,> \n" +
                    ",0					--<sth_promosyon_fl, bit,> \n" +
                    ",0 			--<sth_cari_cinsi, tinyint,> \n" +
                    ",@CIKIS 			--<sth_cari_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_cari_grup_no, tinyint,> \n" +
                    ",''			 		--<sth_isemri_gider_kodu, varchar(25),> \n" +
                    ",''			--<sth_plasiyer_kodu, varchar(25),> \n" +
                    ",(SELECT cari_doviz_cinsi FROM CARI_HESAPLAR WHERE cari_kod = @CIKIS) 		--<sth_har_doviz_cinsi, tinyint,> \n" +
                    ",1 		--<sth_har_doviz_kuru, float,> \n" +
                    ",1 		--<sth_alt_doviz_kuru, float,> \n" +
                    ",1 		--<sth_stok_doviz_cinsi, tinyint,> \n" +
                    ",1		--<sth_stok_doviz_kuru, float,> \n" +
                    ",@MIKTAR 			--<sth_miktar, float,> \n" +
                    ",0 			--<sth_miktar2, float,> \n" +
                    ",1 			--<sth_birim_pntr, tinyint,> \n" +
                    ",0	 			--<sth_tutar, float,> \n" +
                    ",0 			--<sth_iskonto1, float,> \n" +
                    ",0 			--<sth_iskonto2, float,> \n" +
                    ",0 			--<sth_iskonto3, float,> \n" +
                    ",0 			--<sth_iskonto4, float,> \n" +
                    ",0 			--<sth_iskonto5, float,> \n" +
                    ",0 			--<sth_iskonto6, float,> \n" +
                    ",0 			--<sth_masraf1, float,> \n" +
                    ",0 			--<sth_masraf2, float,> \n" +
                    ",0 			--<sth_masraf3, float,> \n" +
                    ",0 			--<sth_masraf4, float,> \n" +
                    ",4			--<sth_vergi_pntr, tinyint,> \n" +
                    ",0 				--<sth_vergi, float,> \n" +
                    ",0 		--<sth_masraf_vergi_pntr, tinyint,> \n" +
                    ",0			--<sth_masraf_vergi, float,> \n" +
                    ",0		 			--<sth_netagirlik, float,> \n" +
                    ",0 			--<sth_odeme_op, int,> \n" +
                    ",'' 			--<sth_aciklama, varchar(50),> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)			 		--<sth_sip_uid, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier) 		--<sth_fat_uid, int,> \n" +
                    ",@GIRIS 			--<sth_giris_depo_no, int,> \n" +
                    ",@GIRIS 			--<sth_cikis_depo_no, int,> \n" +
                    ",GETDATE() 		--<sth_malkbl_sevk_tarihi, datetime,> \n" +
                    ",'' 		--<sth_cari_srm_merkezi, varchar(25),> \n" +
                    ",'' 		--<sth_stok_srm_merkezi, varchar(25),> \n" +
                    ",'18991230'	 			--<sth_fis_tarihi, datetime,> \n" +
                    ",0		 			--<sth_fis_sirano, int,> \n" +
                    ",0 		 			--<sth_vergisiz_fl, bit,> \n" +
                    ",0		 			--<sth_maliyet_ana, float,> \n" +
                    ",0			 		--<sth_maliyet_alternatif, float,> \n" +
                    ",0			 		--<sth_maliyet_orjinal, float,> \n" +
                    ",1 			--<sth_adres_no, int,> \n" +
                    ",@PARTI 			--<sth_parti_kodu, varchar(25),> \n" +
                    ",1	 			--<sth_lot_no, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)						--<sth_kons_uid, smallint,> \n" +
                    ",''		--<sth_proje_kodu, varchar(25),> \n" +
                    ",'' 			--<sth_exim_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_otv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_otv_vergi, float,> \n" +
                    ",0		 			--<sth_brutagirlik, float,> \n" +
                    ",0		--<sth_disticaret_turu, tinyint,> \n" +
                    ",0		 			--<sth_otvtutari, float,> \n" +
                    ",0			--<sth_otvvergisiz_fl, bit,> \n" +
                    ",0					--<sth_oiv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_oiv_vergi, float,> \n" +
                    ",0	 		--<sth_oivvergisiz_fl, bit,> \n" +
                    ",1 		--<sth_fiyat_liste_no, int,> \n" +
                    ",0			 		--<sth_oivtutari, float,> \n" +
                    ",0			 		--<sth_Tevkifat_turu, tinyint,> \n" +
                    ",0					--<sth_nakliyedeposu, int,> \n" +
                    ",0					--<sth_nakliyedurumu, tinyint,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)					--<sth_yetkili_uid, int,> \n" +
                    ",0					--<sth_taxfree_fl, bit,>  \n" +
                    ",0					--<sth_ilave_edilecek_kdv,float,> \n" +
                    ",''					--<sth_ismerkezi_kodu> \n" +
                    ",''					--<sth_HareketGrupKodu1, varchar(25),> \n" + 
                    ",''					--<sth_HareketGrupKodu2, varchar(25),>  \n" +
                    ",''					--<sth_HareketGrupKodu3, varchar(25),>  \n" +
                    ",0					--<sth_Olcu1, float,> \n" +
                    ",0					--<sth_Olcu2, float,> \n" +
                    ",0					--<sth_Olcu3, float,> \n" +
                    ",0					--<sth_Olcu4, float,> \n" +
                    ",0					--<sth_Olcu5, float,> \n" +
                    ",0					--<sth_FormulMiktarNo, tinyint,> \n" +
                    ",0					--<sth_FormulMiktar, float,> \n" +
                    ") " +
                    "SELECT [sth_Guid] FROM @UIDTABLE ",
            param : ['TARIH:string|10','SERI:string|10','SIRA:int','SATIRNO:int','STOK:string|25','CIKIS:string|25',
                    'MIKTAR:float','DURUM:int','GIRIS:string|25','PARTI:string|25']
        },
    },
    {
        name: "YURT DIŞI ALIŞ İRSALİYESİ", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT  " + 
                  "CONVERT(nvarchar(10),TARIH,112) AS TARIH, " + 
                  "SERI AS SERI, " + 
                  "SIRA AS SIRA, " + 
                  "SATIRNO AS SATIRNO, " + 
                  "STOK AS STOK, " + 
                  "PARTI AS PARTI," + 
                  "GIRIS AS GIRIS, " + 
                  "CIKIS AS CIKIS, " + 
                  "BIRIM AS BIRIM, " + 
                  "MIKTAR AS MIKTAR, " + 
                  "CASE DURUM WHEN 11 THEN 0  WHEN 11 THEN 0 WHEN 12 THEN 12 END AS DURUM," +
                  "OZEL AS OZEL " + 
                  "FROM EMIR_HAREKETLERI WHERE TIP = 0 AND CINS = 3 AND DURUM = 12  " 
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT sth_evrakno_seri,sth_evrakno_sira FROM STOK_HAREKETLERI WHERE sth_evrakno_seri = @SERI and sth_evrakno_sira = @SIRA AND sth_tip = 0  AND sth_evraktip = 13 AND sth_satirno =@SATIRNO ",
            param:['SERI:string|50','SIRA:int','SATIRNO:int']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE STOK_HAREKETLERI SET sth_miktar = @MIKTAR " +
            " WHERE sth_evraktip = 13 AND sth_evrakno_seri = @SERI AND sth_evrakno_sira = @SIRA AND sth_satirno = @SATIRNO" ,
            param : ['MIKTAR:float','SERI:string|50','SIRA:int','SATIRNO:int']
        },
        insert : 
        {
            query : "DECLARE @UIDTABLE table([sth_Guid] [uniqueidentifier]) " +
                    "INSERT INTO [STOK_HAREKETLERI] " +
                    "([sth_DBCno] " +
                    ",[sth_SpecRECno] " +
                    ",[sth_iptal] " +
                    ",[sth_fileid] " +
                    ",[sth_hidden] " +
                    ",[sth_kilitli] " +
                    ",[sth_degisti] " +
                    ",[sth_checksum] " +
                    ",[sth_create_user] " +
                    ",[sth_create_date] " +
                    ",[sth_lastup_user] " +
                    ",[sth_lastup_date] " +
                    ",[sth_special1] " +
                    ",[sth_special2] " +
                    ",[sth_special3] " +
                    ",[sth_firmano] " +
                    ",[sth_subeno] " +
                    ",[sth_tarih] " +
                    ",[sth_tip] " +
                    ",[sth_cins] " +
                    ",[sth_normal_iade] " +
                    ",[sth_evraktip] " +
                    ",[sth_evrakno_seri] " +
                    ",[sth_evrakno_sira] " +
                    ",[sth_satirno] " +
                    ",[sth_belge_no] " +
                    ",[sth_belge_tarih] " +
                    ",[sth_stok_kod] " +
                    ",[sth_isk_mas1] " +
                    ",[sth_isk_mas2] " +
                    ",[sth_isk_mas3] " +
                    ",[sth_isk_mas4] " +
                    ",[sth_isk_mas5] " +
                    ",[sth_isk_mas6] " +
                    ",[sth_isk_mas7] " +
                    ",[sth_isk_mas8] " +
                    ",[sth_isk_mas9] " +
                    ",[sth_isk_mas10] " +
                    ",[sth_sat_iskmas1] " +
                    ",[sth_sat_iskmas2] " +
                    ",[sth_sat_iskmas3] " +
                    ",[sth_sat_iskmas4] " +
                    ",[sth_sat_iskmas5] " +
                    ",[sth_sat_iskmas6] " +
                    ",[sth_sat_iskmas7] " +
                    ",[sth_sat_iskmas8] " +
                    ",[sth_sat_iskmas9] " +
                    ",[sth_sat_iskmas10] " +
                    ",[sth_pos_satis] " +
                    ",[sth_promosyon_fl] " +
                    ",[sth_cari_cinsi] " +
                    ",[sth_cari_kodu] " +
                    ",[sth_cari_grup_no] " +
                    ",[sth_isemri_gider_kodu] " +
                    ",[sth_plasiyer_kodu] " +
                    ",[sth_har_doviz_cinsi] " +
                    ",[sth_har_doviz_kuru] " +
                    ",[sth_alt_doviz_kuru] " +
                    ",[sth_stok_doviz_cinsi] " +
                    ",[sth_stok_doviz_kuru] " +
                    ",[sth_miktar] " +
                    ",[sth_miktar2] " +
                    ",[sth_birim_pntr] " +
                    ",[sth_tutar] " +
                    ",[sth_iskonto1] " +
                    ",[sth_iskonto2] " +
                    ",[sth_iskonto3] " +
                    ",[sth_iskonto4] " +
                    ",[sth_iskonto5] " +
                    ",[sth_iskonto6] " +
                    ",[sth_masraf1] " +
                    ",[sth_masraf2] " +
                    ",[sth_masraf3] " +
                    ",[sth_masraf4] " +
                    ",[sth_vergi_pntr] " +
                    ",[sth_vergi] " +
                    ",[sth_masraf_vergi_pntr] " +
                    ",[sth_masraf_vergi] " +
                    ",[sth_netagirlik] " +
                    ",[sth_odeme_op] " +
                    ",[sth_aciklama] " +
                    ",[sth_sip_uid] " +
                    ",[sth_fat_uid] " +
                    ",[sth_giris_depo_no] " +
                    ",[sth_cikis_depo_no] " +
                    ",[sth_malkbl_sevk_tarihi] " +
                    ",[sth_cari_srm_merkezi] " +
                    ",[sth_stok_srm_merkezi] " +
                    ",[sth_fis_tarihi] " +
                    ",[sth_fis_sirano] " +
                    ",[sth_vergisiz_fl] " +
                    ",[sth_maliyet_ana] " +
                    ",[sth_maliyet_alternatif] " +
                    ",[sth_maliyet_orjinal] " +
                    ",[sth_adres_no] " +
                    ",[sth_parti_kodu] " +
                    ",[sth_lot_no] " +
                    ",[sth_kons_uid] " +
                    ",[sth_proje_kodu] " +
                    ",[sth_exim_kodu] " +
                    ",[sth_otv_pntr] " +
                    ",[sth_otv_vergi] " +
                    ",[sth_brutagirlik] " +
                    ",[sth_disticaret_turu] " +
                    ",[sth_otvtutari] " +
                    ",[sth_otvvergisiz_fl] " +
                    ",[sth_oiv_pntr] " +
                    ",[sth_oiv_vergi] " +
                    ",[sth_oivvergisiz_fl] " +
                    ",[sth_fiyat_liste_no] " +
                    ",[sth_oivtutari] " +
                    ",[sth_Tevkifat_turu] " +
                    ",[sth_nakliyedeposu] " +
                    ",[sth_nakliyedurumu] " +
                    ",[sth_yetkili_uid] " +
                    ",[sth_taxfree_fl] " +
                    ",[sth_ilave_edilecek_kdv] " + 
                    ",[sth_ismerkezi_kodu]  " +
                    ",[sth_HareketGrupKodu1] " +
                    ",[sth_HareketGrupKodu2] " +
                    ",[sth_HareketGrupKodu3]   " +
                    ",[sth_Olcu1]   " +
                    ",[sth_Olcu2]   " +
                    ",[sth_Olcu3]   " +
                    ",[sth_Olcu4]   " +
                    ",[sth_Olcu5]   " +
                    ",[sth_FormulMiktarNo]   " +
                    ",[sth_FormulMiktar]   " +
                    ") " +
                    "OUTPUT INSERTED.[sth_Guid] INTO @UIDTABLE " + 
                    "VALUES ( " +
                    "0					--<sth_DBCno, smallint,> \n" +
                    ",0					--<sth_SpecRECno, int,> \n" +
                    ",0	 				--<sth_iptal, bit,> \n" +
                    ",16					 --<sth_fileid, smallint,> \n" +
                    ",0		 			--<sth_hidden, bit,> \n" +
                    ",0		 			--<sth_kilitli, bit,> \n" +
                    ",0		 			--<sth_degisti, bit,> \n" +
                    ",0		 			--<sth_checksum, int,> \n" +
                    ",1 			--<sth_create_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_create_date, datetime,> \n" +
                    ",1			--<sth_lastup_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_lastup_date, datetime,> \n" +
                    ",''		 			--<sth_special1, varchar(4),> \n" +
                    ",''		 			--<sth_special2, varchar(4),> \n" +
                    ",''		 			--<sth_special3, varchar(4),> \n" +
                    ",0 			--<sth_firmano, int,> \n" +
                    ",0 			--<sth_subeno, int,> \n" +
                    ",@TARIH 				--<sth_tarih, datetime,> \n" +
                    ",0 				--<sth_tip, tinyint,> \n" +
                    ",@DURUM				--<sth_cins, tinyint,> \n" +
                    ",0 			--<sth_normal_iade, tinyint,> \n" +
                    ",13 			--<sth_evraktip, tinyint,> \n" +
                    ",@SERI 			--<sth_evrakno_seri, varchar(4),> \n" +
                    ",@SIRA 			--<sth_evrakno_sira, int,> \n" +
                    ",@SATIRNO	--<sip_satirno, int,> \n" +
                    ",'' 			--sth_belge_no, varchar(15),> \n" +
                    ",GETDATE() 			--<sth_belge_tarih, datetime,> \n" +
                    ",@STOK 			--<sth_stok_kod, varchar(25),> \n" +
                    ",0		--<sth_isk_mas1, tinyint,> \n" +
                    ",0		--<sth_isk_mas2, tinyint,> \n" +
                    ",0		--<sth_isk_mas3, tinyint,> \n" +
                    ",0		--<sth_isk_mas4, tinyint,> \n" +
                    ",0		--<sth_isk_mas5, tinyint,> \n" +
                    ",0		--<sth_isk_mas6, tinyint,> \n" +
                    ",0		--<sth_isk_mas7, tinyint,> \n" +
                    ",0		--<sth_isk_mas8, tinyint,> \n" +
                    ",0		--<sth_isk_mas9, tinyint,> \n" +
                    ",0		--<sth_isk_mas10, tinyint,> \n" +
                    ",0			--<sth_sat_iskmas1, bit,> \n" +
                    ",0			--<sth_sat_iskmas2, bit,> \n" +
                    ",0			--<sth_sat_iskmas3, bit,> \n" +
                    ",0			--<sth_sat_iskmas4, bit,> \n" +
                    ",0			--<sth_sat_iskmas5, bit,> \n" +
                    ",0			--<sth_sat_iskmas6, bit,> \n" +
                    ",0			--<sth_sat_iskmas7, bit,> \n" +
                    ",0			--<sth_sat_iskmas8, bit,> \n" +
                    ",0			--<sth_sat_iskmas9, bit,> \n" +
                    ",0 			--<sth_sat_iskmas10, bit,> \n" +
                    ",0					--<sth_pos_satis, bit,> \n" +
                    ",0					--<sth_promosyon_fl, bit,> \n" +
                    ",0 			--<sth_cari_cinsi, tinyint,> \n" +
                    ",@CIKIS 			--<sth_cari_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_cari_grup_no, tinyint,> \n" +
                    ",''			 		--<sth_isemri_gider_kodu, varchar(25),> \n" +
                    ",''			--<sth_plasiyer_kodu, varchar(25),> \n" +
                    ",(SELECT cari_doviz_cinsi FROM CARI_HESAPLAR WHERE cari_kod = @CIKIS) 		--<sth_har_doviz_cinsi, tinyint,> \n" +
                    ",1 		--<sth_har_doviz_kuru, float,> \n" +
                    ",1 		--<sth_alt_doviz_kuru, float,> \n" +
                    ",1 		--<sth_stok_doviz_cinsi, tinyint,> \n" +
                    ",1		--<sth_stok_doviz_kuru, float,> \n" +
                    ",@MIKTAR 			--<sth_miktar, float,> \n" +
                    ",0 			--<sth_miktar2, float,> \n" +
                    ",1 			--<sth_birim_pntr, tinyint,> \n" +
                    ",0	 			--<sth_tutar, float,> \n" +
                    ",0 			--<sth_iskonto1, float,> \n" +
                    ",0 			--<sth_iskonto2, float,> \n" +
                    ",0 			--<sth_iskonto3, float,> \n" +
                    ",0 			--<sth_iskonto4, float,> \n" +
                    ",0 			--<sth_iskonto5, float,> \n" +
                    ",0 			--<sth_iskonto6, float,> \n" +
                    ",0 			--<sth_masraf1, float,> \n" +
                    ",0 			--<sth_masraf2, float,> \n" +
                    ",0 			--<sth_masraf3, float,> \n" +
                    ",0 			--<sth_masraf4, float,> \n" +
                    ",4			--<sth_vergi_pntr, tinyint,> \n" +
                    ",0 				--<sth_vergi, float,> \n" +
                    ",0 		--<sth_masraf_vergi_pntr, tinyint,> \n" +
                    ",0			--<sth_masraf_vergi, float,> \n" +
                    ",0		 			--<sth_netagirlik, float,> \n" +
                    ",0 			--<sth_odeme_op, int,> \n" +
                    ",'' 			--<sth_aciklama, varchar(50),> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)			 		--<sth_sip_uid, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier) 		--<sth_fat_uid, int,> \n" +
                    ",@GIRIS 			--<sth_giris_depo_no, int,> \n" +
                    ",@GIRIS 			--<sth_cikis_depo_no, int,> \n" +
                    ",GETDATE() 		--<sth_malkbl_sevk_tarihi, datetime,> \n" +
                    ",'' 		--<sth_cari_srm_merkezi, varchar(25),> \n" +
                    ",'' 		--<sth_stok_srm_merkezi, varchar(25),> \n" +
                    ",'18991230'	 			--<sth_fis_tarihi, datetime,> \n" +
                    ",0		 			--<sth_fis_sirano, int,> \n" +
                    ",0 		 			--<sth_vergisiz_fl, bit,> \n" +
                    ",0		 			--<sth_maliyet_ana, float,> \n" +
                    ",0			 		--<sth_maliyet_alternatif, float,> \n" +
                    ",0			 		--<sth_maliyet_orjinal, float,> \n" +
                    ",1 			--<sth_adres_no, int,> \n" +
                    ",@PARTI 			--<sth_parti_kodu, varchar(25),> \n" +
                    ",1	 			--<sth_lot_no, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)						--<sth_kons_uid, smallint,> \n" +
                    ",''		--<sth_proje_kodu, varchar(25),> \n" +
                    ",'' 			--<sth_exim_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_otv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_otv_vergi, float,> \n" +
                    ",0		 			--<sth_brutagirlik, float,> \n" +
                    ",3		--<sth_disticaret_turu, tinyint,> \n" +
                    ",0		 			--<sth_otvtutari, float,> \n" +
                    ",0			--<sth_otvvergisiz_fl, bit,> \n" +
                    ",0					--<sth_oiv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_oiv_vergi, float,> \n" +
                    ",0	 		--<sth_oivvergisiz_fl, bit,> \n" +
                    ",1 		--<sth_fiyat_liste_no, int,> \n" +
                    ",0			 		--<sth_oivtutari, float,> \n" +
                    ",0			 		--<sth_Tevkifat_turu, tinyint,> \n" +
                    ",0					--<sth_nakliyedeposu, int,> \n" +
                    ",0					--<sth_nakliyedurumu, tinyint,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)					--<sth_yetkili_uid, int,> \n" +
                    ",0					--<sth_taxfree_fl, bit,>  \n" +
                    ",0					--<sth_ilave_edilecek_kdv,float,> \n" +
                    ",''					--<sth_ismerkezi_kodu> \n" +
                    ",''					--<sth_HareketGrupKodu1, varchar(25),> \n" + 
                    ",''					--<sth_HareketGrupKodu2, varchar(25),>  \n" +
                    ",''					--<sth_HareketGrupKodu3, varchar(25),>  \n" +
                    ",0					--<sth_Olcu1, float,> \n" +
                    ",0					--<sth_Olcu2, float,> \n" +
                    ",0					--<sth_Olcu3, float,> \n" +
                    ",0					--<sth_Olcu4, float,> \n" +
                    ",0					--<sth_Olcu5, float,> \n" +
                    ",0					--<sth_FormulMiktarNo, tinyint,> \n" +
                    ",0					--<sth_FormulMiktar, float,> \n" +
                    ") " +
                    "SELECT [sth_Guid] FROM @UIDTABLE ",
            param : ['TARIH:string|10','SERI:string|10','SIRA:int','SATIRNO:int','STOK:string|25','CIKIS:string|25',
                    'MIKTAR:float','DURUM:int','GIRIS:string|25','PARTI:string|25']
        },
    },
    {
        name: "YURT İÇİ  İADE ALIŞ İRSALİYESİ", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT  " + 
                  "CONVERT(nvarchar(10),TARIH,112) AS TARIH, " + 
                  "SERI AS SERI, " + 
                  "SIRA AS SIRA, " + 
                  "SATIRNO AS SATIRNO, " + 
                  "STOK AS STOK, " + 
                  "PARTI AS PARTI," + 
                  "GIRIS AS GIRIS, " + 
                  "CIKIS AS CIKIS, " + 
                  "BIRIM AS BIRIM, " + 
                  "MIKTAR AS MIKTAR, " + 
                  "DURUM AS DURUM," +
                  "OZEL AS OZEL " + 
                  "FROM EMIR_HAREKETLERI WHERE TIP = 0 AND CINS = 4 AND DURUM = 1   " 
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT sth_evrakno_seri,sth_evrakno_sira FROM STOK_HAREKETLERI WHERE sth_evrakno_seri = @SERI and sth_evrakno_sira = @SIRA AND sth_normal_iade = 1 AND sth_evraktip = 13 AND sth_satirno =@SATIRNO ",
            param:['SERI:string|50','SIRA:int','SATIRNO:int']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE STOK_HAREKETLERI SET sth_miktar = @MIKTAR " +
            " WHERE sth_evraktip = 13 AND sth_evrakno_seri = @SERI AND sth_evrakno_sira = @SIRA AND sth_satirno = @SATIRNO" ,
            param : ['MIKTAR:float','SERI:string|50','SIRA:int','SATIRNO:int']
        },
        
        insert : 
        {
            query : "DECLARE @UIDTABLE table([sth_Guid] [uniqueidentifier]) " +
                    "INSERT INTO [STOK_HAREKETLERI] " +
                    "([sth_DBCno] " +
                    ",[sth_SpecRECno] " +
                    ",[sth_iptal] " +
                    ",[sth_fileid] " +
                    ",[sth_hidden] " +
                    ",[sth_kilitli] " +
                    ",[sth_degisti] " +
                    ",[sth_checksum] " +
                    ",[sth_create_user] " +
                    ",[sth_create_date] " +
                    ",[sth_lastup_user] " +
                    ",[sth_lastup_date] " +
                    ",[sth_special1] " +
                    ",[sth_special2] " +
                    ",[sth_special3] " +
                    ",[sth_firmano] " +
                    ",[sth_subeno] " +
                    ",[sth_tarih] " +
                    ",[sth_tip] " +
                    ",[sth_cins] " +
                    ",[sth_normal_iade] " +
                    ",[sth_evraktip] " +
                    ",[sth_evrakno_seri] " +
                    ",[sth_evrakno_sira] " +
                    ",[sth_satirno] " +
                    ",[sth_belge_no] " +
                    ",[sth_belge_tarih] " +
                    ",[sth_stok_kod] " +
                    ",[sth_isk_mas1] " +
                    ",[sth_isk_mas2] " +
                    ",[sth_isk_mas3] " +
                    ",[sth_isk_mas4] " +
                    ",[sth_isk_mas5] " +
                    ",[sth_isk_mas6] " +
                    ",[sth_isk_mas7] " +
                    ",[sth_isk_mas8] " +
                    ",[sth_isk_mas9] " +
                    ",[sth_isk_mas10] " +
                    ",[sth_sat_iskmas1] " +
                    ",[sth_sat_iskmas2] " +
                    ",[sth_sat_iskmas3] " +
                    ",[sth_sat_iskmas4] " +
                    ",[sth_sat_iskmas5] " +
                    ",[sth_sat_iskmas6] " +
                    ",[sth_sat_iskmas7] " +
                    ",[sth_sat_iskmas8] " +
                    ",[sth_sat_iskmas9] " +
                    ",[sth_sat_iskmas10] " +
                    ",[sth_pos_satis] " +
                    ",[sth_promosyon_fl] " +
                    ",[sth_cari_cinsi] " +
                    ",[sth_cari_kodu] " +
                    ",[sth_cari_grup_no] " +
                    ",[sth_isemri_gider_kodu] " +
                    ",[sth_plasiyer_kodu] " +
                    ",[sth_har_doviz_cinsi] " +
                    ",[sth_har_doviz_kuru] " +
                    ",[sth_alt_doviz_kuru] " +
                    ",[sth_stok_doviz_cinsi] " +
                    ",[sth_stok_doviz_kuru] " +
                    ",[sth_miktar] " +
                    ",[sth_miktar2] " +
                    ",[sth_birim_pntr] " +
                    ",[sth_tutar] " +
                    ",[sth_iskonto1] " +
                    ",[sth_iskonto2] " +
                    ",[sth_iskonto3] " +
                    ",[sth_iskonto4] " +
                    ",[sth_iskonto5] " +
                    ",[sth_iskonto6] " +
                    ",[sth_masraf1] " +
                    ",[sth_masraf2] " +
                    ",[sth_masraf3] " +
                    ",[sth_masraf4] " +
                    ",[sth_vergi_pntr] " +
                    ",[sth_vergi] " +
                    ",[sth_masraf_vergi_pntr] " +
                    ",[sth_masraf_vergi] " +
                    ",[sth_netagirlik] " +
                    ",[sth_odeme_op] " +
                    ",[sth_aciklama] " +
                    ",[sth_sip_uid] " +
                    ",[sth_fat_uid] " +
                    ",[sth_giris_depo_no] " +
                    ",[sth_cikis_depo_no] " +
                    ",[sth_malkbl_sevk_tarihi] " +
                    ",[sth_cari_srm_merkezi] " +
                    ",[sth_stok_srm_merkezi] " +
                    ",[sth_fis_tarihi] " +
                    ",[sth_fis_sirano] " +
                    ",[sth_vergisiz_fl] " +
                    ",[sth_maliyet_ana] " +
                    ",[sth_maliyet_alternatif] " +
                    ",[sth_maliyet_orjinal] " +
                    ",[sth_adres_no] " +
                    ",[sth_parti_kodu] " +
                    ",[sth_lot_no] " +
                    ",[sth_kons_uid] " +
                    ",[sth_proje_kodu] " +
                    ",[sth_exim_kodu] " +
                    ",[sth_otv_pntr] " +
                    ",[sth_otv_vergi] " +
                    ",[sth_brutagirlik] " +
                    ",[sth_disticaret_turu] " +
                    ",[sth_otvtutari] " +
                    ",[sth_otvvergisiz_fl] " +
                    ",[sth_oiv_pntr] " +
                    ",[sth_oiv_vergi] " +
                    ",[sth_oivvergisiz_fl] " +
                    ",[sth_fiyat_liste_no] " +
                    ",[sth_oivtutari] " +
                    ",[sth_Tevkifat_turu] " +
                    ",[sth_nakliyedeposu] " +
                    ",[sth_nakliyedurumu] " +
                    ",[sth_yetkili_uid] " +
                    ",[sth_taxfree_fl] " +
                    ",[sth_ilave_edilecek_kdv] " + 
                    ",[sth_ismerkezi_kodu]  " +
                    ",[sth_HareketGrupKodu1] " +
                    ",[sth_HareketGrupKodu2] " +
                    ",[sth_HareketGrupKodu3]   " +
                    ",[sth_Olcu1]   " +
                    ",[sth_Olcu2]   " +
                    ",[sth_Olcu3]   " +
                    ",[sth_Olcu4]   " +
                    ",[sth_Olcu5]   " +
                    ",[sth_FormulMiktarNo]   " +
                    ",[sth_FormulMiktar]   " +
                    ") " +
                    "OUTPUT INSERTED.[sth_Guid] INTO @UIDTABLE " + 
                    "VALUES ( " +
                    "0					--<sth_DBCno, smallint,> \n" +
                    ",0					--<sth_SpecRECno, int,> \n" +
                    ",0	 				--<sth_iptal, bit,> \n" +
                    ",16					 --<sth_fileid, smallint,> \n" +
                    ",0		 			--<sth_hidden, bit,> \n" +
                    ",0		 			--<sth_kilitli, bit,> \n" +
                    ",0		 			--<sth_degisti, bit,> \n" +
                    ",0		 			--<sth_checksum, int,> \n" +
                    ",1 			--<sth_create_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_create_date, datetime,> \n" +
                    ",1			--<sth_lastup_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_lastup_date, datetime,> \n" +
                    ",''		 			--<sth_special1, varchar(4),> \n" +
                    ",''		 			--<sth_special2, varchar(4),> \n" +
                    ",''		 			--<sth_special3, varchar(4),> \n" +
                    ",0 			--<sth_firmano, int,> \n" +
                    ",0 			--<sth_subeno, int,> \n" +
                    ",@TARIH 				--<sth_tarih, datetime,> \n" +
                    ",0 				--<sth_tip, tinyint,> \n" +
                    ",0				--<sth_cins, tinyint,> \n" +
                    ",1 			--<sth_normal_iade, tinyint,> \n" +
                    ",13 			--<sth_evraktip, tinyint,> \n" +
                    ",@SERI 			--<sth_evrakno_seri, varchar(4),> \n" +
                    ",@SIRA 			--<sth_evrakno_sira, int,> \n" +
                    ",@SATIRNO	--<sip_satirno, int,> \n" +
                    ",'' 			--sth_belge_no, varchar(15),> \n" +
                    ",GETDATE() 			--<sth_belge_tarih, datetime,> \n" +
                    ",@STOK 			--<sth_stok_kod, varchar(25),> \n" +
                    ",0		--<sth_isk_mas1, tinyint,> \n" +
                    ",0		--<sth_isk_mas2, tinyint,> \n" +
                    ",0		--<sth_isk_mas3, tinyint,> \n" +
                    ",0		--<sth_isk_mas4, tinyint,> \n" +
                    ",0		--<sth_isk_mas5, tinyint,> \n" +
                    ",0		--<sth_isk_mas6, tinyint,> \n" +
                    ",0		--<sth_isk_mas7, tinyint,> \n" +
                    ",0		--<sth_isk_mas8, tinyint,> \n" +
                    ",0		--<sth_isk_mas9, tinyint,> \n" +
                    ",0		--<sth_isk_mas10, tinyint,> \n" +
                    ",0			--<sth_sat_iskmas1, bit,> \n" +
                    ",0			--<sth_sat_iskmas2, bit,> \n" +
                    ",0			--<sth_sat_iskmas3, bit,> \n" +
                    ",0			--<sth_sat_iskmas4, bit,> \n" +
                    ",0			--<sth_sat_iskmas5, bit,> \n" +
                    ",0			--<sth_sat_iskmas6, bit,> \n" +
                    ",0			--<sth_sat_iskmas7, bit,> \n" +
                    ",0			--<sth_sat_iskmas8, bit,> \n" +
                    ",0			--<sth_sat_iskmas9, bit,> \n" +
                    ",0 			--<sth_sat_iskmas10, bit,> \n" +
                    ",0					--<sth_pos_satis, bit,> \n" +
                    ",0					--<sth_promosyon_fl, bit,> \n" +
                    ",0 			--<sth_cari_cinsi, tinyint,> \n" +
                    ",@CIKIS 			--<sth_cari_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_cari_grup_no, tinyint,> \n" +
                    ",''			 		--<sth_isemri_gider_kodu, varchar(25),> \n" +
                    ",''			--<sth_plasiyer_kodu, varchar(25),> \n" +
                    ",(SELECT cari_doviz_cinsi FROM CARI_HESAPLAR WHERE cari_kod = @CIKIS) 		--<sth_har_doviz_cinsi, tinyint,> \n" +
                    ",1 		--<sth_har_doviz_kuru, float,> \n" +
                    ",1 		--<sth_alt_doviz_kuru, float,> \n" +
                    ",1 		--<sth_stok_doviz_cinsi, tinyint,> \n" +
                    ",1		--<sth_stok_doviz_kuru, float,> \n" +
                    ",@MIKTAR 			--<sth_miktar, float,> \n" +
                    ",0 			--<sth_miktar2, float,> \n" +
                    ",1 			--<sth_birim_pntr, tinyint,> \n" +
                    ",0	 			--<sth_tutar, float,> \n" +
                    ",0 			--<sth_iskonto1, float,> \n" +
                    ",0 			--<sth_iskonto2, float,> \n" +
                    ",0 			--<sth_iskonto3, float,> \n" +
                    ",0 			--<sth_iskonto4, float,> \n" +
                    ",0 			--<sth_iskonto5, float,> \n" +
                    ",0 			--<sth_iskonto6, float,> \n" +
                    ",0 			--<sth_masraf1, float,> \n" +
                    ",0 			--<sth_masraf2, float,> \n" +
                    ",0 			--<sth_masraf3, float,> \n" +
                    ",0 			--<sth_masraf4, float,> \n" +
                    ",4			--<sth_vergi_pntr, tinyint,> \n" +
                    ",0 				--<sth_vergi, float,> \n" +
                    ",0 		--<sth_masraf_vergi_pntr, tinyint,> \n" +
                    ",0			--<sth_masraf_vergi, float,> \n" +
                    ",0		 			--<sth_netagirlik, float,> \n" +
                    ",0 			--<sth_odeme_op, int,> \n" +
                    ",'' 			--<sth_aciklama, varchar(50),> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)			 		--<sth_sip_uid, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier) 		--<sth_fat_uid, int,> \n" +
                    ",@GIRIS 			--<sth_giris_depo_no, int,> \n" +
                    ",@GIRIS 			--<sth_cikis_depo_no, int,> \n" +
                    ",GETDATE() 		--<sth_malkbl_sevk_tarihi, datetime,> \n" +
                    ",'' 		--<sth_cari_srm_merkezi, varchar(25),> \n" +
                    ",'' 		--<sth_stok_srm_merkezi, varchar(25),> \n" +
                    ",'18991230'	 			--<sth_fis_tarihi, datetime,> \n" +
                    ",0		 			--<sth_fis_sirano, int,> \n" +
                    ",0 		 			--<sth_vergisiz_fl, bit,> \n" +
                    ",0		 			--<sth_maliyet_ana, float,> \n" +
                    ",0			 		--<sth_maliyet_alternatif, float,> \n" +
                    ",0			 		--<sth_maliyet_orjinal, float,> \n" +
                    ",1 			--<sth_adres_no, int,> \n" +
                    ",@PARTI 			--<sth_parti_kodu, varchar(25),> \n" +
                    ",1	 			--<sth_lot_no, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)						--<sth_kons_uid, smallint,> \n" +
                    ",''		--<sth_proje_kodu, varchar(25),> \n" +
                    ",'' 			--<sth_exim_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_otv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_otv_vergi, float,> \n" +
                    ",0		 			--<sth_brutagirlik, float,> \n" +
                    ",0		--<sth_disticaret_turu, tinyint,> \n" +
                    ",0		 			--<sth_otvtutari, float,> \n" +
                    ",0			--<sth_otvvergisiz_fl, bit,> \n" +
                    ",0					--<sth_oiv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_oiv_vergi, float,> \n" +
                    ",0	 		--<sth_oivvergisiz_fl, bit,> \n" +
                    ",1 		--<sth_fiyat_liste_no, int,> \n" +
                    ",0			 		--<sth_oivtutari, float,> \n" +
                    ",0			 		--<sth_Tevkifat_turu, tinyint,> \n" +
                    ",0					--<sth_nakliyedeposu, int,> \n" +
                    ",0					--<sth_nakliyedurumu, tinyint,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)					--<sth_yetkili_uid, int,> \n" +
                    ",0					--<sth_taxfree_fl, bit,>  \n" +
                    ",0					--<sth_ilave_edilecek_kdv,float,> \n" +
                    ",''					--<sth_ismerkezi_kodu> \n" +
                    ",@OZEL					--<sth_HareketGrupKodu1, varchar(25),> \n" + 
                    ",''					--<sth_HareketGrupKodu2, varchar(25),>  \n" +
                    ",''					--<sth_HareketGrupKodu3, varchar(25),>  \n" +
                    ",0					--<sth_Olcu1, float,> \n" +
                    ",0					--<sth_Olcu2, float,> \n" +
                    ",0					--<sth_Olcu3, float,> \n" +
                    ",0					--<sth_Olcu4, float,> \n" +
                    ",0					--<sth_Olcu5, float,> \n" +
                    ",0					--<sth_FormulMiktarNo, tinyint,> \n" +
                    ",0					--<sth_FormulMiktar, float,> \n" +
                    ") " +
                    "SELECT [sth_Guid] FROM @UIDTABLE ",
            param : ['TARIH:string|10','SERI:string|10','SIRA:int','SATIRNO:int','STOK:string|25','CIKIS:string|25',
                    'MIKTAR:float','DURUM:int','GIRIS:string|25','PARTI:string|25','OZEL:string|25']
        },
    },
    {
        name: "SATIŞ İRSALİYESİ", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT  " + 
                  "CONVERT(nvarchar(10),TARIH,112) AS TARIH, " + 
                  "SERI AS SERI, " + 
                  "SIRA AS SIRA, " + 
                  "SATIRNO AS SATIRNO, " + 
                  "STOK AS STOK, " + 
                  "PARTI AS PARTI," + 
                  "GIRIS AS GIRIS, " + 
                  "CIKIS AS CIKIS, " + 
                  "BIRIM AS BIRIM, " + 
                  "MIKTAR AS MIKTAR, " + 
                  "OZEL AS OZEL " + 
                  "FROM EMIR_HAREKETLERI WHERE TIP = 1 AND CINS = 3 AND DURUM = 1" 
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT sth_sip_uid FROM STOK_HAREKETLERI WHERE sth_evrakno_seri = @SERI AND sth_evrakno_sira = @SIRA AND sth_satirno = @SATIRNO ",
            param:['SERI:string|50','SIRA:int','SATIRNO:int']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE STOK_HAREKETLERI SET sth_miktar = @MIKTAR,sth_tutar = (SELECT sip_b_fiyat * @MIKTAR FROM SIPARISLER WHERE sip_Guid = @OZEL), " +
            " sth_iskonto1 = (SELECT sip_iskonto_1/sip_miktar * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) " +
            " WHERE sth_evraktip = 1 AND sth_evrakno_seri = @SERI AND sth_evrakno_sira = @SIRA AND sth_satirno = @SATIRNO" ,
            param : ['MIKTAR:float','OZEL:string|50','SERI:string|50','SIRA:int','SATIRNO:int']
        },
        insert : 
        {
            query : "DECLARE @UIDTABLE table([sth_Guid] [uniqueidentifier]) " +
                    "INSERT INTO [STOK_HAREKETLERI] " +
                    "([sth_DBCno] " +
                    ",[sth_SpecRECno] " +
                    ",[sth_iptal] " +
                    ",[sth_fileid] " +
                    ",[sth_hidden] " +
                    ",[sth_kilitli] " +
                    ",[sth_degisti] " +
                    ",[sth_checksum] " +
                    ",[sth_create_user] " +
                    ",[sth_create_date] " +
                    ",[sth_lastup_user] " +
                    ",[sth_lastup_date] " +
                    ",[sth_special1] " +
                    ",[sth_special2] " +
                    ",[sth_special3] " +
                    ",[sth_firmano] " +
                    ",[sth_subeno] " +
                    ",[sth_tarih] " +
                    ",[sth_tip] " +
                    ",[sth_cins] " +
                    ",[sth_normal_iade] " +
                    ",[sth_evraktip] " +
                    ",[sth_evrakno_seri] " +
                    ",[sth_evrakno_sira] " +
                    ",[sth_satirno] " +
                    ",[sth_belge_no] " +
                    ",[sth_belge_tarih] " +
                    ",[sth_stok_kod] " +
                    ",[sth_isk_mas1] " +
                    ",[sth_isk_mas2] " +
                    ",[sth_isk_mas3] " +
                    ",[sth_isk_mas4] " +
                    ",[sth_isk_mas5] " +
                    ",[sth_isk_mas6] " +
                    ",[sth_isk_mas7] " +
                    ",[sth_isk_mas8] " +
                    ",[sth_isk_mas9] " +
                    ",[sth_isk_mas10] " +
                    ",[sth_sat_iskmas1] " +
                    ",[sth_sat_iskmas2] " +
                    ",[sth_sat_iskmas3] " +
                    ",[sth_sat_iskmas4] " +
                    ",[sth_sat_iskmas5] " +
                    ",[sth_sat_iskmas6] " +
                    ",[sth_sat_iskmas7] " +
                    ",[sth_sat_iskmas8] " +
                    ",[sth_sat_iskmas9] " +
                    ",[sth_sat_iskmas10] " +
                    ",[sth_pos_satis] " +
                    ",[sth_promosyon_fl] " +
                    ",[sth_cari_cinsi] " +
                    ",[sth_cari_kodu] " +
                    ",[sth_cari_grup_no] " +
                    ",[sth_isemri_gider_kodu] " +
                    ",[sth_plasiyer_kodu] " +
                    ",[sth_har_doviz_cinsi] " +
                    ",[sth_har_doviz_kuru] " +
                    ",[sth_alt_doviz_kuru] " +
                    ",[sth_stok_doviz_cinsi] " +
                    ",[sth_stok_doviz_kuru] " +
                    ",[sth_miktar] " +
                    ",[sth_miktar2] " +
                    ",[sth_birim_pntr] " +
                    ",[sth_tutar] " +
                    ",[sth_iskonto1] " +
                    ",[sth_iskonto2] " +
                    ",[sth_iskonto3] " +
                    ",[sth_iskonto4] " +
                    ",[sth_iskonto5] " +
                    ",[sth_iskonto6] " +
                    ",[sth_masraf1] " +
                    ",[sth_masraf2] " +
                    ",[sth_masraf3] " +
                    ",[sth_masraf4] " +
                    ",[sth_vergi_pntr] " +
                    ",[sth_vergi] " +
                    ",[sth_masraf_vergi_pntr] " +
                    ",[sth_masraf_vergi] " +
                    ",[sth_netagirlik] " +
                    ",[sth_odeme_op] " +
                    ",[sth_aciklama] " +
                    ",[sth_sip_uid] " +
                    ",[sth_fat_uid] " +
                    ",[sth_giris_depo_no] " +
                    ",[sth_cikis_depo_no] " +
                    ",[sth_malkbl_sevk_tarihi] " +
                    ",[sth_cari_srm_merkezi] " +
                    ",[sth_stok_srm_merkezi] " +
                    ",[sth_fis_tarihi] " +
                    ",[sth_fis_sirano] " +
                    ",[sth_vergisiz_fl] " +
                    ",[sth_maliyet_ana] " +
                    ",[sth_maliyet_alternatif] " +
                    ",[sth_maliyet_orjinal] " +
                    ",[sth_adres_no] " +
                    ",[sth_parti_kodu] " +
                    ",[sth_lot_no] " +
                    ",[sth_kons_uid] " +
                    ",[sth_proje_kodu] " +
                    ",[sth_exim_kodu] " +
                    ",[sth_otv_pntr] " +
                    ",[sth_otv_vergi] " +
                    ",[sth_brutagirlik] " +
                    ",[sth_disticaret_turu] " +
                    ",[sth_otvtutari] " +
                    ",[sth_otvvergisiz_fl] " +
                    ",[sth_oiv_pntr] " +
                    ",[sth_oiv_vergi] " +
                    ",[sth_oivvergisiz_fl] " +
                    ",[sth_fiyat_liste_no] " +
                    ",[sth_oivtutari] " +
                    ",[sth_Tevkifat_turu] " +
                    ",[sth_nakliyedeposu] " +
                    ",[sth_nakliyedurumu] " +
                    ",[sth_yetkili_uid] " +
                    ",[sth_taxfree_fl] " +
                    ",[sth_ilave_edilecek_kdv] " + 
                    ",[sth_ismerkezi_kodu]  " +
                    ",[sth_HareketGrupKodu1] " +
                    ",[sth_HareketGrupKodu2] " +
                    ",[sth_HareketGrupKodu3]   " +
                    ",[sth_Olcu1]   " +
                    ",[sth_Olcu2]   " +
                    ",[sth_Olcu3]   " +
                    ",[sth_Olcu4]   " +
                    ",[sth_Olcu5]   " +
                    ",[sth_FormulMiktarNo]   " +
                    ",[sth_FormulMiktar]   " +
                    ") " +
                    "OUTPUT INSERTED.[sth_Guid] INTO @UIDTABLE " + 
                    "VALUES ( " +
                    "0					--<sth_DBCno, smallint,> \n" +
                    ",0					--<sth_SpecRECno, int,> \n" +
                    ",0	 				--<sth_iptal, bit,> \n" +
                    ",16					 --<sth_fileid, smallint,> \n" +
                    ",0		 			--<sth_hidden, bit,> \n" +
                    ",0		 			--<sth_kilitli, bit,> \n" +
                    ",0		 			--<sth_degisti, bit,> \n" +
                    ",0		 			--<sth_checksum, int,> \n" +
                    ",1 			--<sth_create_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_create_date, datetime,> \n" +
                    ",1			--<sth_lastup_user, smallint,> \n" +
                    ",GETDATE() 			--<sth_lastup_date, datetime,> \n" +
                    ",''		 			--<sth_special1, varchar(4),> \n" +
                    ",''		 			--<sth_special2, varchar(4),> \n" +
                    ",''		 			--<sth_special3, varchar(4),> \n" +
                    ",0 			--<sth_firmano, int,> \n" +
                    ",0 			--<sth_subeno, int,> \n" +
                    ",@TARIH 				--<sth_tarih, datetime,> \n" +
                    ",1 				--<sth_tip, tinyint,> \n" +
                    ",(SELECT CASE sip_cins WHEN 0 THEN 0 WHEN 3 THEN 12 END FROM SIPARISLER WHERE sip_Guid =@OZEL) 				--<sth_cins, tinyint,> \n" +
                    ",0 			--<sth_normal_iade, tinyint,> \n" +
                    ",1 			--<sth_evraktip, tinyint,> \n" +
                    ",@SERI 			--<sth_evrakno_seri, varchar(4),> \n" +
                    ",@SIRA 			--<sth_evrakno_sira, int,> \n" +
                    ",@SATIRNO	--<sip_satirno, int,> \n" +
                    ",'' 			--sth_belge_no, varchar(15),> \n" +
                    ",GETDATE() 			--<sth_belge_tarih, datetime,> \n" +
                    ",@STOK 			--<sth_stok_kod, varchar(25),> \n" +
                    ",0		--<sth_isk_mas1, tinyint,> \n" +
                    ",0		--<sth_isk_mas2, tinyint,> \n" +
                    ",0		--<sth_isk_mas3, tinyint,> \n" +
                    ",0		--<sth_isk_mas4, tinyint,> \n" +
                    ",0		--<sth_isk_mas5, tinyint,> \n" +
                    ",0		--<sth_isk_mas6, tinyint,> \n" +
                    ",0		--<sth_isk_mas7, tinyint,> \n" +
                    ",0		--<sth_isk_mas8, tinyint,> \n" +
                    ",0		--<sth_isk_mas9, tinyint,> \n" +
                    ",0		--<sth_isk_mas10, tinyint,> \n" +
                    ",0			--<sth_sat_iskmas1, bit,> \n" +
                    ",0			--<sth_sat_iskmas2, bit,> \n" +
                    ",0			--<sth_sat_iskmas3, bit,> \n" +
                    ",0			--<sth_sat_iskmas4, bit,> \n" +
                    ",0			--<sth_sat_iskmas5, bit,> \n" +
                    ",0			--<sth_sat_iskmas6, bit,> \n" +
                    ",0			--<sth_sat_iskmas7, bit,> \n" +
                    ",0			--<sth_sat_iskmas8, bit,> \n" +
                    ",0			--<sth_sat_iskmas9, bit,> \n" +
                    ",0 			--<sth_sat_iskmas10, bit,> \n" +
                    ",0					--<sth_pos_satis, bit,> \n" +
                    ",0					--<sth_promosyon_fl, bit,> \n" +
                    ",0 			--<sth_cari_cinsi, tinyint,> \n" +
                    ",@GIRIS 			--<sth_cari_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_cari_grup_no, tinyint,> \n" +
                    ",''			 		--<sth_isemri_gider_kodu, varchar(25),> \n" +
                    ",''			--<sth_plasiyer_kodu, varchar(25),> \n" +
                    ",(SELECT sip_doviz_cinsi FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_har_doviz_cinsi, tinyint,> \n" +
                    ",(SELECT sip_doviz_kuru FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_har_doviz_kuru, float,> \n" +
                    ",(SELECT sip_alt_doviz_kuru FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_alt_doviz_kuru, float,> \n" +
                    ",(SELECT sip_doviz_cinsi FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_stok_doviz_cinsi, tinyint,> \n" +
                    ",(SELECT sip_doviz_kuru FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_stok_doviz_kuru, float,> \n" +
                    ",@MIKTAR 			--<sth_miktar, float,> \n" +
                    ",0 			--<sth_miktar2, float,> \n" +
                    ",1 			--<sth_birim_pntr, tinyint,> \n" +
                    ",(SELECT sip_b_fiyat * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL)	 			--<sth_tutar, float,> \n" +
                    ",(SELECT sip_iskonto_1/sip_miktar * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto1, float,> \n" +
                    ",(SELECT sip_iskonto_2/sip_miktar  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto2, float,> \n" +
                    ",(SELECT sip_iskonto_3/sip_miktar  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto3, float,> \n" +
                    ",(SELECT sip_iskonto_4/sip_miktar  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto4, float,> \n" +
                    ",(SELECT sip_iskonto_5/sip_miktar  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto5, float,> \n" +
                    ",(SELECT sip_iskonto_6/sip_miktar  * @MIKTAR FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_iskonto6, float,> \n" +
                    ",0 			--<sth_masraf1, float,> \n" +
                    ",0 			--<sth_masraf2, float,> \n" +
                    ",0 			--<sth_masraf3, float,> \n" +
                    ",0 			--<sth_masraf4, float,> \n" +
                    ",(SELECT sip_vergi_pntr FROM SIPARISLER WHERE sip_Guid =@OZEL)			--<sth_vergi_pntr, tinyint,> \n" +
                    ",(SELECT sip_vergi FROM SIPARISLER WHERE sip_Guid =@OZEL) 				--<sth_vergi, float,> \n" +
                    ",(SELECT sip_masvergi_pntr FROM SIPARISLER WHERE sip_Guid =@OZEL) 		--<sth_masraf_vergi_pntr, tinyint,> \n" +
                    ",(SELECT sip_masvergi FROM SIPARISLER WHERE sip_Guid =@OZEL) 			--<sth_masraf_vergi, float,> \n" +
                    ",0		 			--<sth_netagirlik, float,> \n" +
                    ",0 			--<sth_odeme_op, int,> \n" +
                    ",(SELECT sip_aciklama  FROM SIPARISLER WHERE sip_Guid =@OZEL)  			--<sth_aciklama, varchar(50),> \n" +
                    ",@OZEL			 		--<sth_sip_uid, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier) 		--<sth_fat_uid, int,> \n" +
                    ",@CIKIS 			--<sth_giris_depo_no, int,> \n" +
                    ",@CIKIS 			--<sth_cikis_depo_no, int,> \n" +
                    ",GETDATE() 		--<sth_malkbl_sevk_tarihi, datetime,> \n" +
                    ",'' 		--<sth_cari_srm_merkezi, varchar(25),> \n" +
                    ",'' 		--<sth_stok_srm_merkezi, varchar(25),> \n" +
                    ",'18991230'	 			--<sth_fis_tarihi, datetime,> \n" +
                    ",0		 			--<sth_fis_sirano, int,> \n" +
                    ",(SELECT sip_vergisiz_fl FROM SIPARISLER WHERE sip_Guid =@OZEL) 		 			--<sth_vergisiz_fl, bit,> \n" +
                    ",0		 			--<sth_maliyet_ana, float,> \n" +
                    ",0			 		--<sth_maliyet_alternatif, float,> \n" +
                    ",0			 		--<sth_maliyet_orjinal, float,> \n" +
                    ",1 			--<sth_adres_no, int,> \n" +
                    ",@PARTI 			--<sth_parti_kodu, varchar(25),> \n" +
                    ",1	 			--<sth_lot_no, int,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)						--<sth_kons_uid, smallint,> \n" +
                    ",''		--<sth_proje_kodu, varchar(25),> \n" +
                    ",'' 			--<sth_exim_kodu, varchar(25),> \n" +
                    ",0		 			--<sth_otv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_otv_vergi, float,> \n" +
                    ",0		 			--<sth_brutagirlik, float,> \n" +
                    ",1		--<sth_disticaret_turu, tinyint,> \n" +
                    ",0		 			--<sth_otvtutari, float,> \n" +
                    ",0			--<sth_otvvergisiz_fl, bit,> \n" +
                    ",0					--<sth_oiv_pntr, tinyint,> \n" +
                    ",0		 			--<sth_oiv_vergi, float,> \n" +
                    ",0	 		--<sth_oivvergisiz_fl, bit,> \n" +
                    ",1 		--<sth_fiyat_liste_no, int,> \n" +
                    ",0			 		--<sth_oivtutari, float,> \n" +
                    ",0			 		--<sth_Tevkifat_turu, tinyint,> \n" +
                    ",0					--<sth_nakliyedeposu, int,> \n" +
                    ",0					--<sth_nakliyedurumu, tinyint,> \n" +
                    ",cast(cast(0 as binary) as uniqueidentifier)					--<sth_yetkili_uid, int,> \n" +
                    ",0					--<sth_taxfree_fl, bit,>  \n" +
                    ",0					--<sth_ilave_edilecek_kdv,float,> \n" +
                    ",''					--<sth_ismerkezi_kodu> \n" +
                    ",''					--<sth_HareketGrupKodu1, varchar(25),> \n" + 
                    ",''					--<sth_HareketGrupKodu2, varchar(25),>  \n" +
                    ",''					--<sth_HareketGrupKodu3, varchar(25),>  \n" +
                    ",0					--<sth_Olcu1, float,> \n" +
                    ",0					--<sth_Olcu2, float,> \n" +
                    ",0					--<sth_Olcu3, float,> \n" +
                    ",0					--<sth_Olcu4, float,> \n" +
                    ",0					--<sth_Olcu5, float,> \n" +
                    ",0					--<sth_FormulMiktarNo, tinyint,> \n" +
                    ",0					--<sth_FormulMiktar, float,> \n" +
                    ") " +
                    "SELECT [sth_Guid] FROM @UIDTABLE ",
            param : ['TARIH:string|10','SERI:string|10','SIRA:int','STOK:string|25','CIKIS:string|25','SATIRNO:int',
                    'MIKTAR:float','OZEL:string|50','GIRIS:string|25','PARTI:string|25']
        },
    },
    {
        name: "PARTİ LOT", //GÖRÜNEN ADI
        source : //KAYNAK VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"NTGDB",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        target : //HEDEF VERİTABANI BAĞLANTISI
        {
            server: "DEMO;1436",
            database:"MikroDB_V16_MOPSAN2020",
            uid:"nitrogen",
            pwd:"lp8462+"
        },
        auto: 100000,  //OTOMATİK AKTARIM YAPILACAKSA BURAYA MİLİSANİYE CİNSİNDEN SÜRE YAZILIR (1000 = 1 SN) UNDEFINED VEYA BU KEY TANIMLANMAZSA OTOMATİK AKTARILMAZ.
        select :    //KAYITLARIN GETİRİLECEĞİ SELECT SORGUSU
        {
            query:"SELECT  " + 
                  "KODU AS pl_partikodu, " + 
                  "STOK AS pl_stokkodu, " + 
                  "SKT AS SKT " + 
                  "FROM PARTILER WHERE OTARIH >= GETDATE() - 10 " 
        },
        control:    //KAYITLAR KARŞI TARAFADA VAR İSE GÜNCELLEMESİ İÇİN KONTROL SORGUSU
        {
            query: "SELECT pl_partikodu FROM PARTILOT WHERE pl_partikodu = @pl_partikodu",
            param:['pl_partikodu:string|50']
        },
        update:     //UPDATE SORGUSU
        {
            query: "UPDATE PARTILOT SET pl_uretim_tar = (pl_son_kullanim_tar - (SELECT CASE sto_yer_kod WHEN '' THEN 0 ELSE sto_yer_kod END FROM STOKLAR WHERE STOKLAR.sto_kod = PARTILOT.pl_stokkodu)) WHERE [pl_partikodu] = @pl_partikodu " ,
            param : ['pl_partikodu:string|25','pl_stokkodu:string|25']
        },
        insert : 
        {
            query : "INSERT INTO [dbo].[PARTILOT] " +
           "([pl_DBCno] " +
            ",[pl_SpecRECno] " +
            ",[pl_iptal] " +
            ",[pl_fileid] " +
            ",[pl_hidden] " +
            ",[pl_kilitli] " +
            ",[pl_degisti] " +
            ",[pl_checksum] " +
            ",[pl_create_user] " +
            ",[pl_create_date] " +
            ",[pl_lastup_user] " +
            ",[pl_lastup_date] " +
            ",[pl_ozelkod1] " +
            ",[pl_ozelkod2] " +
            ",[pl_ozelkod3] " +
            ",[pl_partikodu] " +
            ",[pl_lotno] " +
            ",[pl_stokkodu] " +
            ",[pl_aciklama] " +
            ",[pl_olckalkdeg_deg1] " +
            ",[pl_olckalkdeg_deg2] " +
            ",[pl_olckalkdeg_deg3] " +
            ",[pl_olckalkdeg_deg4] " +
            ",[pl_olckalkdeg_deg5] " +
            ",[pl_olckalkdeg_deg6] " +
            ",[pl_olckalkdeg_deg7] " +
            ",[pl_olckalkdeg_deg8] " +
            ",[pl_olckalkdeg_deg9] " +
            ",[pl_olckalkdeg_deg10] " +
            ",[pl_olckalkdeg_aciklama1] " +
            ",[pl_olckalkdeg_aciklama2] " +
            ",[pl_olckalkdeg_aciklama3] " +
            ",[pl_olckalkdeg_aciklama4] " +
            ",[pl_olckalkdeg_aciklama5] " +
            ",[pl_olckalkdeg_aciklama6] " +
            ",[pl_olckalkdeg_aciklama7] " +
            ",[pl_olckalkdeg_aciklama8] " +
            ",[pl_olckalkdeg_aciklama9] " +
            ",[pl_olckalkdeg_aciklama10] " +
            ",[pl_son_kullanim_tar] " +
            ",[pl_DaraliKilo] " +
            ",[pl_SafiKilo] " +
            ",[pl_En] " +
            ",[pl_Boy] " +
            ",[pl_Yukseklik] " +
            ",[pl_OzgulAgirlik] " +
            ",[pl_kod1] " +
            ",[pl_kod2] " +
            ",[pl_kod3] " +
            ",[pl_kod4] " +
            ",[pl_kod5] " +
            ",[pl_kod6] " +
            ",[pl_kod7] " +
            ",[pl_kod8] " +
            ",[pl_kod9] " +
            ",[pl_kod10] " +
            ",[pl_uretim_tar])" +
            "VALUES " +
            "(0 \n" +
            ",0 \n" +
            ",0 \n" +
            ",153 \n" +
            ",0 \n" +
            ",0 \n" +
            ",0 \n" +
            ",0 \n" +
            ",1						--<pl_create_user, smallint,> \n" +
            ",CONVERT(VARCHAR(10),GETDATE(),112)	--<pl_create_date, datetime,> \n" +
            ",1						--<pl_lastup_user, smallint,> \n" +
            ",CONVERT(VARCHAR(10),GETDATE(),112)	--<pl_lastup_date, datetime,> \n" +
            ",''									--<pl_ozelkod1, nvarchar(4),> \n" +
            ",''									--<pl_ozelkod2, nvarchar(4),> \n" +
            ",''									--<pl_ozelkod3, nvarchar(4),> \n" +
            ",@pl_partikodu						--<pl_partikodu, nvarchar(25),> \n" +
            ",1							--<pl_lotno, int,> \n" +
            ",@pl_stokkodu						--<pl_stokkodu, nvarchar(25),> \n" +
            ",''									--<pl_aciklama, nvarchar(50),> \n" +
            ",0									--<pl_olckalkdeg_deg1, float,> \n" +
            ",0									--<pl_olckalkdeg_deg2, float,> \n" +
            ",0									--<pl_olckalkdeg_deg3, float,> \n" +
            ",0									--<pl_olckalkdeg_deg4, float,> \n" +
            ",0									--<pl_olckalkdeg_deg5, float,> \n" +
            ",0									--<pl_olckalkdeg_deg6, float,> \n" +
            ",0									--<pl_olckalkdeg_deg7, float,> \n" +
            ",0									--<pl_olckalkdeg_deg8, float,> \n" +
            ",0									--<pl_olckalkdeg_deg9, float,> \n" +
            ",0									--<pl_olckalkdeg_deg10, float,> \n" +
            ",''									--<pl_olckalkdeg_aciklama1, nvarchar(25),> \n" +
            ",''									--<pl_olckalkdeg_aciklama2, nvarchar(25),> \n" +
            ",''									--<pl_olckalkdeg_aciklama3, nvarchar(25),> \n" +
            ",''									--<pl_olckalkdeg_aciklama4, nvarchar(25),> \n" +
            ",''									--<pl_olckalkdeg_aciklama5, nvarchar(25),> \n" +
            ",''									--<pl_olckalkdeg_aciklama6, nvarchar(25),> \n" + 
            ",''									--<pl_olckalkdeg_aciklama7, nvarchar(25),> \n" +
            ",''									--<pl_olckalkdeg_aciklama8, nvarchar(25),> \n" +
            ",''									--<pl_olckalkdeg_aciklama9, nvarchar(25),> \n" +
            ",''									--<pl_olckalkdeg_aciklama10, nvarchar(25),> \n" +
            ",@SKT						--<pl_son_kullanim_tar, datetime,> \n" +
            ",0									--<pl_DaraliKilo, float,> \n" +
            ",0									--<pl_SafiKilo, float,> \n" +
            ",0									--<pl_En, float,> \n" +
            ",0									--<pl_Boy, float,> \n" +
            ",0									--<pl_Yukseklik, float,> \n" +
            ",0									--<pl_OzgulAgirlik, float,> \n" +
            ",''									--<pl_kod1, nvarchar(25),> \n" +
            ",''									--<pl_kod2, nvarchar(25),> \n" +
            ",''									--<pl_kod3, nvarchar(25),> \n" +
            ",''									--<pl_kod4, nvarchar(25),> \n" +
            ",''									--<pl_kod5, nvarchar(25),> \n" +
            ",''									--<pl_kod6, nvarchar(25),> \n" +
            ",''									--<pl_kod7, nvarchar(25),> \n" +
            ",''									--<pl_kod8, nvarchar(25),> \n" +
            ",''									--<pl_kod9, nvarchar(25),> \n" +
            ",''									--<pl_kod10, nvarchar(25),> \n" +
            ",''									--<pl_uretim_tar, datetime(25),> \n" +
            ") " ,
        param : ['pl_partikodu:string|25','pl_stokkodu:string|25','SKT:string|25']
        },
    }
]
module.exports = Process;