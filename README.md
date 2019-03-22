
<img src="https://github.com/Smart-flowerpot/Smart-Flowerpot-Arduino/blob/master/Alternatif_Logo.png" />

Smart Flowerpot Nedir ?
Smart Flowerpot, BIL496 Bitirme Projesi dersi “Ev Hayatını Kolaylaştıran Sistemler” konusu kapsamında 5 kişilik takımımızla birlikte geliştirdiğimiz projedir.
Takım üyeleri :
1. Ömer Faruk Kurular 141101039
2. Bekir Berk Şenel 141101056
3. Musa Ünal 151101003
4. Mithat Kurt 111101033
5. Orhan Onar 131101063
Kullanıcının Android uygulaması üzerinden bitkisinin bulunduğu ortamdaki havanın anlık nem değerini, bitkisinin bulunduğu toprağın anlık nem değerini, ortamın anlık sıcaklık değerini ve buna benzer bilgileri kontrol edebildiği; aynı zamanda aplikasyon üzerinde tanımlı 73 adet bitki türünden istediği bitkiyi veya kendi bitkisini seçerek her bitki için önceden tanımlanmış optimal değerler üzerinden ortamdaki değerleri tanımlı verilerle kıyaslayan uygulamamız ile uyarı alabildiği ve aldığı uyarılara göre dilediği taktirde uzaktan kontrol ile tek tuşla sulama yapabildiği bir akıllı saksı sistemidir.
Smart Flowerpot Uygulaması Nasıl Kullanılır ?
Uygulama tamamiyle kullanıcı dostu ve basit bir arayüz kullanılarak tasarlanmıştır. Kullanıcı uygulamaya giriş yaptığında Home (Ana Sayfa) üzerinde “+” butonuna basarak önceden tanımlı 73 bitki türü içerisinden kendi bitkisini ekleyebilir. Bitki türlerinin önceden tanımlanmasının asıl amacı ilgili bitki türünün optimal değerlerinin önceden tanımlanmış olması ve gerekli değerlerin ortam koşullarınca sağlanmaması halinde kullanıcının uyarılabilmesidir. Kullanıcı bitkisini sisteme ekledikten sonra tekrar Home üzerinden bitkisinin bulunduğu butona basarak kendi bitkisine yönlendirilir. Böylece açılan sayfa üzerinden bitkisinin optimal değerlerini kontrol edebilir ve dilerse ”Water me” butonuna tıklayarak sulama işlemini gerçekleştirebilir. (Şekil 2)

Smart Flowerpot Projesinde Neler Kullanıldı ?
Donanım
- Nodemcu iOT kartı
- Arduino
- Blackboard
- Toprak nem sensörü
- Hava nem ısı sensörü
- Su motoru
- Buzzer
- Işık sensörü
Yazılım
- Android
- Mqtt server
- Arduino
- Html
- Php
Smart Flowerpot Projesi Nasıl Çalışır ?
Projenin çalışma prensibi Şekil 1’ de detaylı olarak gösterilmiştir.


<img src="https://github.com/Smart-flowerpot/Smart-Flowerpot-Arduino/blob/master/Schema1.png" />
<img src="https://github.com/Smart-flowerpot/Smart-Flowerpot-Arduino/blob/master/Schema3.png" />