#ifndef LIFECOMPONENT_H
#define LIFECOMPONENT_H

#include <inttypes.h>
#include <math.h>
#include <float.h>

class LifeComponent
{
public:
	LifeComponent() : m_maxHp(0.0), m_hp(0.0), m_dmg(0.0) {}
	LifeComponent(double maxHp, double dmg) : m_maxHp(fabs(maxHp)), m_hp(m_maxHp), m_dmg(fabs(dmg)) {}
	LifeComponent(double maxHp, double hp, double dmg) : m_maxHp(fabs(maxHp)), m_hp(fabs(hp) >= m_maxHp ? m_maxHp : fabs(hp)), m_dmg(fabs(dmg)) {}

public: //Functionality
	inline void heal(double hp) { m_hp += fabs(hp); m_hp = (m_hp > m_maxHp ? m_maxHp : m_hp); }
	inline void takeDmg(double dmg) { m_hp -= fabs(dmg); m_hp = (m_hp < 0.0 ? 0.0 : m_hp); }
	inline bool isDead() const { return (m_hp < DBL_EPSILON); }
	inline bool isFullHp() const { return ((m_maxHp - m_hp) < DBL_EPSILON); }

public: //Setters
	inline void setMaxHealth(double maxHp) { m_maxHp = fabs(maxHp); }
	inline void setHealth(double hp) { m_hp = (fabs(hp) >= m_maxHp ? m_maxHp : fabs(hp)); }
	inline void setDmg(double dmg) { m_dmg = fabs(dmg); }

public: //Getters
	inline double getMaxHealth() const { return m_maxHp; }
	inline double getHealth() const { return m_hp; }
	inline double getDmg() const { return m_dmg; }

private: //Members
	double m_maxHp;
	double m_hp;
	double m_dmg;
};

#endif //LIFECOMPONENT_H