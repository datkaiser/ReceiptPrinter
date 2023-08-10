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
    serial.setPortName("COM5");
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

    QByteArray Header = Ctext+ alignCenter + "Store-Nguyen Van Troi\n";
    Header += alignCenter +"66 Nguyen Van Troi,Phu Nhuan HCM\n";
    Header += alignCenter +"(84) 28 3842 2171\n";
    Header += "======================\n";


    Header += alignLeft+"Member Name  :\n";
    Header += "Card No      : XXXXXXXX627\n";
    Header += "Level        : Unassigned\n";
    Header += "Star Balance : 0\n";
    Header += "Card Balance : 0\n\n";
    Header += "40801632 Le Van Hoang Quan\n";
    Header += "--------------------------------\n";



    QString productName = "Order 123";
    QString productPrice = "Jul 25,2023 15:25PM";

        // Tính toán số lượng dấu cách cần thêm để đảm bảo căn đều
    int totalWidth = 32;  // Tổng chiều dài cố định
    int spaceWidth = totalWidth - codec->fromUnicode(productName).length() - codec->fromUnicode(productPrice).length();
    QByteArray spaces(spaceWidth, ' ');

        // Tạo dữ liệu dòng hóa đơn
    QByteArray productLine = codec->fromUnicode(productName) + spaces + codec->fromUnicode(productPrice) + "\n";


    QByteArray Header1 = "--------------------------------\n";;



    QString productName1 = "1 BINH WTBL";
    QString productPrice1 = "830,000";
    int totalWidth1 = 32;  // Tổng chiều dài cố định
    int spaceWidth1 = totalWidth1 - codec->fromUnicode(productName1).length() - codec->fromUnicode(productPrice1).length();
    QByteArray spaces1(spaceWidth1, ' ');
    QByteArray productLine1 = codec->fromUnicode(productName1) + spaces1 + codec->fromUnicode(productPrice1) + "\n";


    QByteArray Header2 = "--------------------------------\n";;


    QString productName2 = "Sub Total";
    QString productPrice2 = "768,519";
    int totalWidth2 = 32;  // Tổng chiều dài cố định
    int spaceWidth2 = totalWidth2 - codec->fromUnicode(productName2).length() - codec->fromUnicode(productPrice2).length();
    QByteArray spaces2(spaceWidth2, ' ');
    QByteArray productLine2 = codec->fromUnicode(productName2) + spaces2 + codec->fromUnicode(productPrice2) + "\n";


    QString productName3 = "Tax";
    QString productPrice3 = "61,481";
    int totalWidth3 = 32;
    int spaceWidth3 = totalWidth3 - codec->fromUnicode(productName3).length() - codec->fromUnicode(productPrice3).length();
    QByteArray spaces3(spaceWidth3, ' ');
    QByteArray productLine3 = codec->fromUnicode(productName3) + spaces3 + codec->fromUnicode(productPrice3) + "\n";


    QString productName4 = Ctext+"Total";
    QString productPrice4 = Btext+"830,000";
    int totalWidth4 = 38;
    int spaceWidth4 = totalWidth4 - codec->fromUnicode(productName4).length() - codec->fromUnicode(productPrice4).length();
    QByteArray spaces4(spaceWidth4, ' ');
    QByteArray productLine4 = codec->fromUnicode(productName4) + spaces4 + codec->fromUnicode(productPrice4) + "\n";


    QByteArray Header3 = "--------------------------------\n";;


    QString productName5 = Ctext+ "SBUX CARD";
    QString productPrice5 = "830,000";
    int totalWidth5 = 35;
    int spaceWidth5 = totalWidth5 - codec->fromUnicode(productName5).length() - codec->fromUnicode(productPrice5).length();
    QByteArray spaces5(spaceWidth5, ' ');
    QByteArray productLine5 = codec->fromUnicode(productName5) + spaces5 + codec->fromUnicode(productPrice5) + "\n";


    QByteArray Header4 = alignLeft+ "XXXXXXXXXXXXX627\n";

    QString productName6 = "Change Due";
    QString productPrice6 = "0";
    int totalWidth6 = 32;
    int spaceWidth6 = totalWidth6 - codec->fromUnicode(productName6).length() - codec->fromUnicode(productPrice6).length();
    QByteArray spaces6(spaceWidth6, ' ');
    QByteArray productLine6 = codec->fromUnicode(productName6) + spaces6 + codec->fromUnicode(productPrice6) + "\n";

    QByteArray Header5 = "--------------------------------\n";
    Header5 += "Vui long yeu xuat hoa don GTGT ngay khi giao dich truoc hoan tat thanh toan.Cac yeu cau xuat GTGT sau khi hoan tat giao dich se khong duoc thuc hien\n";
    Header5 += alignCenter+"Cam on\n";
    Header5 += "--------------------------------\n";

    sendCommand(serial, Header);
    sendCommand(serial, productLine);
    sendCommand(serial, Header1);
    sendCommand(serial, productLine1);
    sendCommand(serial, Header2);
    sendCommand(serial, productLine2);
    sendCommand(serial, productLine3);
    sendCommand(serial, productLine4);
    sendCommand(serial, Header3);
    sendCommand(serial, productLine5);
    sendCommand(serial, Header4);
    sendCommand(serial, productLine6);
    sendCommand(serial, Header5);

    serial.close();

    return a.exec();
}
