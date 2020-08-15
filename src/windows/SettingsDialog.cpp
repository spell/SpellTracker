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
