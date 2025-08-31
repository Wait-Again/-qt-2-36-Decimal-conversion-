#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jzzhq.h"
#include <QString>
#include <QMessageBox>

// 主窗口构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), converter(new Jzzhq) // 初始化UI组件和转换器对象
{
    ui->setupUi(this);
    setWindowTitle(""); // 设置空窗口标题

    // 连接按钮点击信号与槽函数
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::onConvertClicked);
    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::onSwapBasesClicked);
}

MainWindow::~MainWindow()
{
    delete converter;
    delete ui;
}

// 数值转换按钮点击事件处理
void MainWindow::onConvertClicked()
{
    // 获取用户输入
    QString num = ui->inputNumber->text();         // 待转换数字
    QString fromBaseStr = ui->fromBase->text();    // 原始进制
    QString toBaseStr = ui->toBase->text();        // 目标进制

    // 进制参数有效性检查
    bool ok1, ok2;
    int fromBase = fromBaseStr.toInt(&ok1);
    int toBase = toBaseStr.toInt(&ok2);

    // 检查进制范围（2-36）
    if (!ok1 || !ok2 || fromBase < 2 || fromBase > 36 || toBase < 2 || toBase > 36) {
        ui->result->setText("Invalid base range (2-36).");
        return;
    }

    // 调用转换器执行实际转换
    std::string result = converter->change(fromBase, toBase, 5, num.toStdString());

    // 处理转换结果
    if (result == "error") {
        // 错误状态显示（红色文字）
        ui->result->setStyleSheet("color: red;");
        ui->result->setText(QString("'%1' is not a valid base-%2 number.").arg(num).arg(fromBase));
    } else {
        // 成功转换显示（绿色文字）
        ui->result->setStyleSheet("color: green;");
        ui->result->setText(QString::fromStdString(result));
    }
}

// 交换进制按钮点击事件处理
void MainWindow::onSwapBasesClicked()
{
    // 交换原始进制和目标进制的值
    QString tmp = ui->fromBase->text();
    ui->fromBase->setText(ui->toBase->text());
    ui->toBase->setText(tmp);
}
