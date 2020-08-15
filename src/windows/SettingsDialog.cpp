#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget* parent) :
		QDialog(parent),
		ui(new Ui::SettingsDialog) {
	ui->setupUi(this);

	connect(ui->slider_IconScale, &QSlider::valueChanged, this, &SettingsDialog::iconScaleValueChanged);
	connect(ui->spinBox_IconSpacing, QOverload<int>::of(&QSpinBox::valueChanged),
	        this, &SettingsDialog::iconSpacingValueChanged);
}

SettingsDialog::~SettingsDialog() {
	delete ui;
}

void SettingsDialog::done(int i) {
	QDialog::done(i);
	settings.setValue("itemTracker/iconSpacing", ui->spinBox_IconSpacing->value());
	settings.setValue("itemTracker/iconScale", ui->slider_IconScale->value());
}

void SettingsDialog::reloadSettings() {
	ui->spinBox_IconSpacing->setValue(settings.value("itemTracker/iconSpacing", 8).toInt());
	ui->slider_IconScale->setValue(settings.value("itemTracker/iconScale", 100).toInt());
}
