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



template<typename T>
const T sfp::trig<T>::table_tenperstep[] = {
	0.0,								//sin(0)
	0.17364817766693034885171662676931,	//sin(10)
	0.34202014332566873304409961468226,	//sin(20)
	0.5,								//sin(30)
	0.64278760968653932632264340990726,	//sin(40)
	0.76604444311897803520239265055542,	//sin(50)
	0.86602540378443864676372317075294,	//sin(60)
	0.93969262078590838405410927732473,	//sin(70)
	0.98480775301220805936674302458952,	//sin(80)
	1.0									//sin(90)
};


template<typename T>
const T sfp::trig<T>::table_oneperstep[] = {
	1.0,								//cos(0)
	0.99984769515639123915701155881391,	//cos(1)
	0.99939082701909573000624344004393,	//cos(2)
	0.99862953475457387378449205843944,	//cos(3)
	0.99756405025982424761316268064426,	//cos(4)
	0.99619469809174553229501040247389,	//cos(5)
	0.99452189536827333692269194498057,	//cos(6)
	0.99254615164132203498006158933058,	//cos(7)
	0.99026806874157031508377486734485,	//cos(8)
	0.98768834059513772619004024769344	//cos(9)
};



template<typename T>
const T sfp::trig<T>::pi = 3.14159265358979323846;

template<typename T>
const T sfp::trig<T>::pi_by_2 = 6.18318530717958647692;

template<typename T>
const T sfp::trig<T>::pi_over_2 = 1.57079632679489661923;

template<typename T>
const T sfp::trig<T>::pi_over_180 = 0.017453292519943295769236907684886;




template<typename T>
T sfp::trig<T>::sin(const angle<T>& ang)
{
	return std::sin(ang.radians());
	
/*	int a = static_cast<int>(angle * 0.1);
	if(a < 10 && a > -1)
		return fast_sin(angle);
	T b = angle - 10 * a;
	
	return sin_tablevalue(a) * cos_smallvalue(static_cast<int>(b + 0.5)) + cos_tablevalue(a) * b * pi_over_180;*/
}


template<typename T>
T sfp::trig<T>::cos(const angle<T>& ang)
{
	return std::cos(ang.radians());
	
/*	int a = static_cast<int>(angle * 0.1);
	if(a < 10 && a > -1)
		return fast_cos(angle);
	T b = angle - 10 * a;
	
	return cos_tablevalue(a) * cos_smallvalue(static_cast<int>(b + 0.5)) - sin_tablevalue(a) * b * pi_over_180;*/
}


template<typename T>
T sfp::trig<T>::tan(const angle<T>& ang)
{
	return std::tan(ang.radians());
	
/*	int a = static_cast<int>(angle * 0.1);
	if(a < 10 && a > -1)
		return fast_tan(angle);
	T b = angle - 10 * a;
	
	T sinx = sin_tablevalue(a);
	T siny = b * pi_over_180;
	T cosx = cos_tablevalue(a);
	T cosy = cos_smallvalue(static_cast<int>(b + 0.5));
	
	return (sinx * cosy + siny * cosx) / (cosx * cosy - sinx * siny);*/
}


template<typename T>
T sfp::trig<T>::fast_sin(const angle<T>& ang)
{
	int a = static_cast<int>(ang.degrees() * 0.1);
	T b = ang.degrees() - 10 * a;
	
	return table_tenperstep[a] * table_oneperstep[static_cast<int>(b)] + table_tenperstep[9-a] * b * pi_over_180;
}


template<typename T>
T sfp::trig<T>::fast_cos(const angle<T>& ang)
{
	int a = static_cast<int>(ang.degrees() * 0.1);
	T b = ang.degrees() - 10 * a;
	
	return table_tenperstep[9-a] * table_oneperstep[static_cast<int>(b)] - table_tenperstep[a] * b * pi_over_180;
}


template<typename T>
T sfp::trig<T>::fast_tan(const angle<T>& ang) //FIXME
{
	int a = static_cast<int>(ang.degrees() * 0.1);
	T b = ang.degrees() - 10 * a;
	
	return (table_tenperstep[a] * table_oneperstep[static_cast<int>(b)] + b * pi_over_180 * table_tenperstep[9-a]) /
			(table_tenperstep[9-a] * table_oneperstep[static_cast<int>(b)] - table_tenperstep[a] * b * pi_over_180);
}



template<typename T>
angle<T> sfp::trig<T>::asin(T value)
{
	return angle<T>::from_radian(std::asin(value));
}


template<typename T>
angle<T> sfp::trig<T>::acos(T value)
{
	return angle<T>::from_radians(std::acos(value));
}


template<typename T>
angle<T> sfp::trig<T>::atan(T value)
{
	return angle<T>::from_radians(std::atan(value));
}


template<typename T>
angle<T> sfp::trig<T>::atan2(T y, T x)
{
	return angle<T>::from_radians(std::atan2(y, x));
}



template<typename T>
T sfp::trig<T>::sin_tablevalue(int val)
{
	if(val > 36) val -= 36 * static_cast<int>(val / 36);
	
	if(val < 9)
	{
		return table_tenperstep[val];
	}
	else if(val < 18)
	{
		return table_tenperstep[18-val];
	}
	else if(val < 27)
	{
		return -table_tenperstep[val-18];
	}
	else
	{
		return -table_tenperstep[36-val];
	}
}


template<typename T>
T sfp::trig<T>::cos_tablevalue(int val)
{
	if(val > 36) val -= 36 * static_cast<int>(val / 36);
	
	if(val < 9)
	{
		return table_tenperstep[9-val];
	}
	else if(val < 18)
	{
		return -table_tenperstep[val-9];
	}
	else if(val < 27)
	{
		return -table_tenperstep[27-val];
	}
	else
	{
		return table_tenperstep[val-27];
	}
}


template<typename T>
T sfp::trig<T>::cos_smallvalue(unsigned int val)
{
	return table_oneperstep[val];
}



