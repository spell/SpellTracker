//
// Created by Jesse on 8/4/2020.
//

#ifndef SPELLTRACKER_ITEM_H
#define SPELLTRACKER_ITEM_H

#include <optional>

#include <QPixmap>
#include <QString>

class Item {
public:
	struct Upgrade {
	public:
		explicit Upgrade(const QString& name);

		Upgrade(const QString& name, const QPixmap& icon);

		QString name;
		std::optional<QPixmap> icon;
		std::optional<QPixmap> grayscaleIcon;
	};

protected:
	QString id;
	QString category;
	QList<Upgrade> upgrades;

public:
	Item() = default;

	Item(const QStringView& id, const QStringView& category);

	void addUpgrade(const QString& name, const QPixmap& icon);

	[[nodiscard]] const QString& getId() const {
		return id;
	}

	[[nodiscard]] const QString& getCategory() const {
		return category;
	}

	[[nodiscard]] int getUpgradeLevels() const {
		return upgrades.length();
	}

	[[nodiscard]] const Upgrade& getUpgradeLevel(int level) const {
		if (level <= 0) {
			return upgrades.first();
		}

		if (level - 1 < upgrades.length()) {
			return upgrades.at(level - 1);
		}

		return upgrades.last();
	}
};


#endif //SPELLTRACKER_ITEM_H
