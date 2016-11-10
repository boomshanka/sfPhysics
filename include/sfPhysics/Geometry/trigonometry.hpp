/******************************************************************************
 **	sfPhysics - A simple 2D physics engine
 ** Copyright (C) 2011  Olaf Vogt aka Boomshanka
 ** 
 ** This program is free software; you can redistribute it and/or modify it
 ** under the terms of the GNU General Public License as published by the Free
 ** Software Foundation; either version 3 of the License, or (at your option)
 ** any later version. 
 ** 
 ** This program is distributed in the hope that it will be useful, but WITHOUT
 ** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 ** FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 ** more details. 
 ** 
 ** You should have received a copy of the GNU General Public License along
 ** with this program; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/


#pragma once

#include <cmath>
#include <sfPhysics/Geometry/angle.hpp>


namespace sfp
{
	template<typename T>
	class trig
	{
		private:
			static const T table_tenperstep[];		
			static const T table_oneperstep[];
			
			static T sin_tablevalue(int val);
			static T cos_tablevalue(int val);
			static T cos_smallvalue(unsigned int val);
			
		public:
			static const T pi;
			static const T pi_by_2;
			static const T pi_over_2;
			static const T pi_over_180;
			
			
			static T sin(const angle<T>& ang);
			static T cos(const angle<T>& ang);
			static T tan(const angle<T>& ang);
			
			static T fast_sin(const angle<T>& ang);
			static T fast_cos(const angle<T>& ang);
			static T fast_tan(const angle<T>& ang);
			
			static angle<T> asin(T value);
			static angle<T> acos(T value);
			static angle<T> atan(T value);
			static angle<T> atan2(T y, T x);
			
	};

	
	#include <sfPhysics/Geometry/trigonometry.inl>
	
	
	typedef trig<float> trigf;
	typedef trig<double> trigd;
	typedef trig<long double> trigld;
	
	
} // namespace sfp


