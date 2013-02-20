#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTextCodec>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFont>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QFont font;
	font.setPointSize(26);
	font.setFamily("Droid Sans Fallback");

	app.setFont(font);

	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
	QWidget *pWidget = new QWidget;
	QLabel label(pWidget);

	pWidget->showMaximized();
	label.setText(QObject::tr("注意看我的字体abcdefg"));

	QPushButton *btn = new QPushButton(QObject::tr("关闭"));
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(&label);
	layout->addWidget(btn);
	pWidget->setLayout(layout);

	QObject::connect(btn, SIGNAL(clicked()), pWidget, SLOT(close()));
	pWidget->show();

	return app.exec();
}

