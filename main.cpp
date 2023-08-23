#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTextCodec>
#include <QDebug>

void sendCommand(QSerialPort& serial, const QByteArray& command) {
    qint64 bytesWritten = serial.write(command);

    if (bytesWritten == -1) {
        qDebug() << "Lỗi gửi lệnh!";
    } else {
        qDebug() << "Đã gửi" << bytesWritten << "byte lệnh";
    }

    serial.waitForBytesWritten();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSerialPort serial;
    serial.setPortName("ttymxc2");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Không thể mở cổng RS232!";
        return 1;
    }

    // Gửi lệnh căn lề trung tâm và in đậm chữ (thay thế bằng mã lệnh thực tế) \x1B\x45\x01
    QTextCodec* codec = QTextCodec::codecForName("Windows-1258");

    QByteArray alignLeft = "\x1B\x61\x30";
    QByteArray alignCenter = "\x1B\x61\x31";
    QByteArray Btext = "\x1B\x45\x01";
    QByteArray Ctext = "\x1B\x45\x30";

    QByteArray Header = Ctext+ alignCenter + "Thong Tin Thanh Toan\n";
    Header += alignCenter +"Payment information\n";
    Header += "================================\n";

    QString productName = "Gio vao";
    QString productPrice = "Jul 25,2023 15:25PM";


    int totalWidth = 32;
    int spaceWidth = totalWidth - codec->fromUnicode(productName).length() - codec->fromUnicode(productPrice).length();
    QByteArray spaces(spaceWidth, ' ');

        // Tạo dữ liệu dòng hóa đơn
    QByteArray checkinTime = codec->fromUnicode(productName) + spaces + codec->fromUnicode(productPrice) + "\n";



    QString productName1 = "Gio ra";
    QString productPrice1 = "Jul 25,2023 15:25PM";
    int totalWidth1 = 32;
    int spaceWidth1 = totalWidth1 - codec->fromUnicode(productName1).length() - codec->fromUnicode(productPrice1).length();
    QByteArray spaces1(spaceWidth1, ' ');
    QByteArray checkoutTime = codec->fromUnicode(productName1) + spaces1 + codec->fromUnicode(productPrice1) + "\n";



    QString productName2 = "Bien So Xe";
    QString productPrice2 = "768,519";
    int totalWidth2 = 32;
    int spaceWidth2 = totalWidth2 - codec->fromUnicode(productName2).length() - codec->fromUnicode(productPrice2).length();
    QByteArray spaces2(spaceWidth2, ' ');
    QByteArray licenseplate = codec->fromUnicode(productName2) + spaces2 + codec->fromUnicode(productPrice2) + "\n";


    QString productName3 = "So Tien";
    QString productPrice3 = "61,481";
    int totalWidth3 = 32;
    int spaceWidth3 = totalWidth3 - codec->fromUnicode(productName3).length() - codec->fromUnicode(productPrice3).length();
    QByteArray spaces3(spaceWidth3, ' ');
    QByteArray amout = codec->fromUnicode(productName3) + spaces3 + codec->fromUnicode(productPrice3) + "\n";

    QByteArray Header3 = "--------------------------------\n";;

    QString productName4 = "Phuong thuc thanh toan";
    QString productPrice4 = "xxx";
    int totalWidth4 = 32;
    int spaceWidth4 = totalWidth4 - codec->fromUnicode(productName4).length() - codec->fromUnicode(productPrice4).length();
    QByteArray spaces4(spaceWidth4, ' ');
    QByteArray payment = codec->fromUnicode(productName4) + spaces4 + codec->fromUnicode(productPrice4) + "\n";



    sendCommand(serial, Header);
    sendCommand(serial, checkinTime);
    sendCommand(serial, checkoutTime);
    sendCommand(serial, licenseplate);
    sendCommand(serial, amout);
    sendCommand(serial, Header3);
    sendCommand(serial, payment);


    serial.close();

    return a.exec();
}
