#pragma once
#include "constants.hpp"
#include "Laws.hpp"
#include "Vector.hpp"

#include <vector>

double Viscosity(double mass) {
	return VISCOSITY_CONST * mass / (FIELD_DX * FIELD_DY);
}

class Field_of_mass {
 public:
	Field_of_mass(int n, int m) : maxn_(n), maxm_(m) {
		mass_ = std::vector<std::vector<double>>(n);
		speed_ = std::vector<std::vector<Vector>>(n);
		viscosity_ = std::vector<std::vector<double>>(n);
		for(size_t i = 0; i < n; i++) {
			mass_[i] = std::vector<double>(m);
			speed_[i] = std::vector<Vector>(m);
			viscosity_[i] = std::vector<double>(m);
			for(size_t j = 0; j < m; j++) {
				mass_[i][j] = 0;
				viscosity_[i][j] = DEFAULT_VISCOSITY;
				speed_[i][j] = Vector(0, 0);
			}
		}
	}
	Field_of_mass(std::vector<std::vector<double>>& mass) : mass_(mass) {
		maxn_ = mass.size();
		maxm_ = mass[0].size();
		speed_ = std::vector<std::vector<Vector>>(maxn_);
		for(size_t i = 0; i < maxn_; ++i) {
			speed_[i] = std::vector<Vector>(maxm_);
		}
		RecalculateViscosity_();
	}
	Field_of_mass(std::vector<std::vector<double>>&& mass) : mass_(std::move(mass)) {
		maxn_ = mass.size();
		maxm_ = mass[0].size();
		speed_ = std::vector<std::vector<Vector>>(maxn_);
		for(size_t i = 0; i < maxn_; ++i) {
			speed_[i] = std::vector<Vector>(maxm_);
		}
		RecalculateViscosity_();
	}
	Field_of_mass(std::vector<std::vector<double>>&& mass, std::vector<std::vector<Vector>>&& speed) : mass_(std::move(mass)), speed_(std::move(speed)) {
		maxn_ = mass.size();
		maxm_ = mass[0].size();
		RecalculateViscosity_();
	}
	Field_of_mass(Field_of_mass&& f) : mass_(std::move(f.mass_)), speed_(std::move(f.speed_)), viscosity_(std::move(f.viscosity_)), maxn_(f.maxn_), maxm_(f.maxm_) {}
	Field_of_mass(const Field_of_mass& f) : mass_(std::move(f.mass_)), speed_(std::move(f.speed_)), viscosity_(std::move(f.viscosity_)), maxn_(f.maxn_), maxm_(f.maxm_) {}

	void operator=(Field_of_mass&& f) {
		mass_ = std::move(f.mass_);
		speed_ = std::move(f.speed_);
		viscosity_ = std::move(f.viscosity_);
		maxn_ = f.maxn_;
		maxm_ = f.maxm_;
	}
	Field_of_mass& operator=(Field_of_mass& f) {
		mass_ = std::move(f.mass_);
		speed_ = std::move(f.speed_);
		viscosity_ = std::move(f.viscosity_);
		maxn_ = f.maxn_;
		maxm_ = f.maxm_;
		return *this;
	}
	double GetMass(int i, int j) const {
		return mass_[i][j];
	}
	void SetMass(int i, int j, double newMass) {
		mass_[i][j] = newMass;
		RecalculateViscosity_(i, j);
	}
	void AddMass(int i, int j, double additionalMass) {
		mass_[i][j] += additionalMass;
		RecalculateViscosity_(i, j);
	}

	Vector GetSpeed(int i, int j) const {
		return speed_[i][j];
	}
	void SetSpeed(int i, int j, const Vector& v) {
		speed_[i][j] = v;
	}
	void AddSpeed(int i, int j, const Vector& v) {
		speed_[i][j] += v;
	}
	
	double GetViscosity(int i, int j) const {
		return viscosity_[i][j];
	}

	int GetN() const {
		return maxn_;
	}
	int GetM() const {
		return maxm_;
	}
 private:
	void RecalculateViscosity_(int i = -1, int j = -1) {
		if (i >= 0 && j >= 0) {
			for(size_t q = 0; q < maxn_; q++) {
				for(size_t w = 0; w < maxm_; w++) {
					viscosity_[q][w] = Viscosity(mass_[q][w]);
				}
			}
		}
		else {
			viscosity_[i][j] = Viscosity(mass_[i][j]);
		}
	}
 protected:
	std::vector<std::vector<double>> mass_;
	std::vector<std::vector<Vector>> speed_;
	std::vector<std::vector<double>> viscosity_;
	int maxn_;
	int maxm_;
};
