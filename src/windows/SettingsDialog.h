#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
	class SettingsDialog;
}

class SettingsDialog : public QDialog {
Q_OBJECT

signals:

	void iconSpacingValueChanged(int spacing);

	void iconScaleValueChanged(int scale);

public:
	explicit SettingsDialog(QWidget* parent = nullptr);

	~SettingsDialog() override;

	void done(int i) override;

public slots:
	void reloadSettings();

private:
	Ui::SettingsDialog* ui;
	QSettings settings;
};

#endif // SETTINGSDIALOG_H
