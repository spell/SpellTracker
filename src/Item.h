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
protected:
	QString id;
	QString name;
	QString category; // technically optional!
	int icon;

	// Optional values
	QStringList progressiveUpgrades;
	int maxCount{0};

public:
	Item() = default;

	Item(QStringView id, QStringView name, QStringView category, int icon = 0);

	void setUpgrades(const QStringList& upgradeIds);
	void setMaxCount(int count);

	[[nodiscard]] const QString& getId() const {
		return id;
	}

	[[nodiscard]] const QString& getCategory() const {
		return category;
	}

	[[nodiscard]] const QString& getName() const {
		return name;
	}

	[[nodiscard]] int getIcon() const {
		return icon;
	}

	[[nodiscard]] bool isProgressive() const {
		return !progressiveUpgrades.isEmpty();
	}

	[[nodiscard]] int levels() const {
		return progressiveUpgrades.size();
	}

	[[nodiscard]] QString getUpgradeItemId(int level) const {
		if (!isProgressive()) {
			return id;
		}

		if (level <= 0) {
			return progressiveUpgrades.first();
		}

		if (level > progressiveUpgrades.size()) {
			return progressiveUpgrades.last();
		}

		return progressiveUpgrades.at(level - 1);
	}

	[[nodiscard]] bool isStacking() const {
		return maxCount != 0;
	}

	[[nodiscard]] int maxStacks() const {
		return maxCount;
	}
};

Q_DECLARE_METATYPE(Item);

#endif //SPELLTRACKER_ITEM_H
