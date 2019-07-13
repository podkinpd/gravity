#pragma once
#include "constants.hpp"
#include "Vector.hpp"
#include "Field_of_mass.hpp"

#include <cmath>
#include <math.h>
#include <iostream>

namespace Laws {
	Vector TerribbleForce(const Field_of_mass& f, int i1, int j1, int i2, int j2) {
	    Vector v12 = Vector(FIELD_DX * (i2 - i1), FIELD_DY * (j2 - j1));
   		double dist = v12.GetABS();
    	dist = dist * dist * dist;
    
    	return v12 * (GravConst * f.GetMass(i1, j1) * f.GetMass(i2, j2)/(dist));
	}

	class Env {
	 public:
	 	Env(int i, int j, int n, int m) {
			n--;
			m--;
			if (i > 0) {
				if (j > 0) data_.push_back(std::make_pair(i-1,j-1));
				data_.push_back(std::make_pair(i-1,j));
				if (j < m) data_.push_back(std::make_pair(i-1,j+1));
			}
			if (j > 0) data_.push_back(std::make_pair(i,j-1));
			if (j < m) data_.push_back(std::make_pair(i,j+1));
			if (i < n) {
				if (j > 0) data_.push_back(std::make_pair(i+1,j-1));
				data_.push_back(std::make_pair(i+1,j));
				if (j < m) data_.push_back(std::make_pair(i+1,j+1));
			}
		}
		std::vector<std::pair<int,int>> data_;
	};
	
	Field_of_mass ResultField(Field_of_mass& f) {
		int n = f.GetN();
		int m = f.GetM();
		std::vector<std::vector<Vector>> currentSpeedField(n);
		std::vector<std::vector<Vector>> currentGravityField(n);
		for(size_t i = 0; i < n; i++) {
			currentGravityField[i] = std::vector<Vector>(m);
			currentSpeedField[i] = std::vector<Vector>(m);
			for(size_t j = 0; j < m; j++) {
				currentGravityField[i][j] = Vector();
				if(f.GetMass(i, j) > 1e+2) {
					for(size_t q = 0; q < n; q++) {
						for(size_t w = 0; w < m; w++) {
							if (((q != i) || (w != j)) && f.GetMass(q, w) > 1e+2) {
								currentGravityField[i][j] += TerribbleForce(f, i, j, q, w);
							}
						}
					}
				}
				currentSpeedField[i][j] = f.GetSpeed(i, j) + (currentGravityField[i][j] * DT / 2);
			}
		}
		Field_of_mass result(n, m);
		for(size_t i = 0; i < n; i++) {
			for(size_t j = 0; j < m; j++) {
				Env env(i, j, n, m);
				for(size_t e = 0; e < env.data_.size(); e++) {
					int q = env.data_[e].first, w = env.data_[e].second;
					Vector diffSpeed = currentSpeedField[i][j] - currentSpeedField[q][w];
//					std::cout << diffSpeed.GetX() << ' ' << diffSpeed.GetY() << std::endl;
					Vector l(q - i, w - j);
					double sc = diffSpeed.Scalar(l);
					if (sc >= 0) {
						if (sqrt(1 - sc * sc) * l.GetABS() <= FIELD_DX) {
							currentGravityField[i][j] -= diffSpeed * (f.GetViscosity(i, j) * f.GetViscosity(q, w));
						}
					}
				}
				result.SetSpeed(i, j, f.GetSpeed(i, j) + currentGravityField[i][j] * DT);
//				std::cout << result.GetSpeed(i, j) << std::endl;
				double newPosX = i, newPosY = j;
				newPosX += f.GetSpeed(i, j).GetX() * DT + 0.5 * currentGravityField[i][j].GetX() * DT * DT;
				newPosY += f.GetSpeed(i, j).GetY() * DT + 0.5 * currentGravityField[i][j].GetY() * DT * DT;
				int posX, posY;
				
				posX = (int)(floor(newPosX));
				posY = (int)(floor(newPosY));
//				std::cout << system("ps -ela") << std::endl;
//				std::cout << i << ' ' << j << ' ' << newPosX << ' ' << newPosY << std::endl;
				if (posX >= 0 and posX< n and posY >= 0 and posY < m) result.AddMass(posX, posY, f.GetMass(i, j) / (FIELD_DX * FIELD_DY) * (1 - fabs(newPosX - posX)) * (1 - fabs(newPosY - posY)));
				posY++;
				if (posX >= 0 and posX< n and posY >= 0 and posY < m) result.AddMass(posX, posY, f.GetMass(i, j) / (FIELD_DX * FIELD_DY) * (1 - fabs(newPosX - posX)) * (1 - fabs(newPosY - posY)));
				posX++;
				if (posX >= 0 and posX< n and posY >= 0 and posY < m) result.AddMass(posX, posY, f.GetMass(i, j) / (FIELD_DX * FIELD_DY) * (1 - fabs(newPosX - posX)) * (1 - fabs(newPosY - posY)));
				posY--;
				if (posX >= 0 and posX< n and posY >= 0 and posY < m) result.AddMass(posX, posY, f.GetMass(i, j) / (FIELD_DX * FIELD_DY) * (1 - fabs(newPosX - posX)) * (1 - fabs(newPosY - posY)));
			}
		}
		return result;
	}
}
