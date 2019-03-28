#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "vector.h"

#define LOCATION false
#define INCREMENT true

namespace EEProj
{
	template <uint8_t N> class Pid
	{
	public:
		// Constructor for PID2D
		Pid()
		{
			_kp   = 1;
			_ki   = 0;
			_kd   = 0;
			_isIncre = true;
		}
		
		Pid(float initial_p, float initial_i, float initial_d, bool isIncre = true)
		{
			_kp   = initial_p;
			_ki   = initial_i;
			_kd	  = initial_d;
			_isIncre = isIncre;
		}
		
		// get Kp, Ki, Kd
		double&	kp()			{ return _kp; }
		double&	ki()			{ return _ki; }
		double&	kd()			{ return _kd; }
		bool&   isIncre()		{ return _isIncre; }
		double	kp()	  const { return _kp; }
		double	ki()	  const { return _ki; }
		double	kd()	  const { return _kd; }
		bool    isIncre() const { return _isIncre; }
		
		// Interfaces
		Vector<N> get_p()   	{ return ((_error[0] - (_isIncre ? _error[1] : Vector<N>())) * _kp); }
		Vector<N> get_i()   	{ return (_integrator[0] * _ki); }
		Vector<N> get_d()   	{ return (_derivative[0] * _kd); }
		Vector<N> get_pid() 	{ return (get_p() + get_i() + get_d()); }
		
		// New Record
		void newInput(Vector<N> error, unsigned long dt)
		{
			if (dt > 0) {
				for(int i = N; i > 0; i--) {
					_dt[i] = _dt[i - 1];
					_error[i] = _error[i - 1];
					_integrator[i] = _integrator[i - 1];
					_derivative[i] = _derivative[i - 1];
				}
				_dt[0] = double(dt) / 1000000;
				_error[0] = error;
				if (_ki > 0) { cal_integrator(); }
				if (_kd > 0) { cal_derivative(); }
			}
		}

	private:
		// parameters
		double			_kp;
		double			_ki;
		double			_kd;
	
		// flags
		bool			_isIncre;
	
		// internal variables
		double			_dt[3];			       // timestep in  seconds of: [k, k-1, k-2]
		Vector<N>		_integrator[3];    // integrator   value   of: [k, k-1, k-2]
		Vector<N>		_error[3];         // input(Error) value   of: [k, k-1, k-2]
		Vector<N>		_derivative[3];    // derivative   value   of: [k, k-1, k-2]
		
		// calculations
		void cal_integrator()
		{
			if (_isIncre) {
				_integrator[0]  = _error[0] * _dt[0];
			} else {
				_integrator[0] = _integrator[0] + (_error[1] * _dt[1]);
			}
		}
		
		void cal_derivative()
		{      
			_derivative[0] = (_error[0] - _error[1]) / _dt[0];
			if (_isIncre && (_dt[1] > 0)) {
				_derivative[0] = _derivative[0] - (_error[1] - _error[2]) / _dt[1];
			}
		}
	};
};
