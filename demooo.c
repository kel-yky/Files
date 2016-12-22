int mode = 1;
int x; //tested optimal working speed
int speed[3] = {0};
int timer = 0; //in milliseconds
int prev_stage_time = 0;
int stage_time = 0;
int encoder[3] = {0}; //storing encoder value in encoder ticks
int e_vel[3] = {0};  //storing encoder velocity
int diff[3] = {0}; //error
int counter = 0;
int ACONST = 0.02;
int t_interval1; //travel time between stops(short d)
int t_interval2; //stop time 

int button_time = 0;

int get_real_velocity(*encoder,stagetime); //function prototype

int main()
{
	//init
	
	if (timer != get_real_ticks())
	{
		timer = get_real_ticks();
	}
	
	button_time = 
	enum STATE
	{
		BEGIN,
		ACCEL,
		DECEL,
		STOP,
		UTURN,
		LONGACC,
		LONGDEC,
		END,
	};
	
	speed[0] = x;
	speed[1] = 0.5x;
	speed[2] = 0.5x;
	
	while(1)
	{
		if (timer % 10 == 0)
		{
			button_update();
		}
		switch(mode)
		{
			case 1: //auto
				if (button_press(button_id) != 0)
				{
					mode = 2;
					break;
				}
				if (stage == BEGIN)
				{
					stagetime = timer - prev_stage_time;
					motor_control(MOTOR1, speed[0]);
					motor_control(MOTOR2, speed[1]);
					motor_control(MOTOR3, speed[2]);
					if (get_count(1) != 0)
					{
						stage = ACCEL;
					}
				}
				if (stage == ACCEL)
				{
					stagetime = timer - prev_stage_time;
					get_real_velocity(encoder, stagetime);
					for (i = 0; i < 3; i++)
					{
						diff[i] = e_vel[i] - speed[i];
						if (diff[i] < 0)
						{
							speed[i] += ACONST*diff[i];
						}
						else if (diff[i] > 0)
						{
							speed[i] -= ACONST*diff[i];
						}
						motor_control(MOTOR1, speed[0]);
						motor_control(MOTOR2, speed[1]);
						motor_control(MOTOR3, speed[2]);
					}
					if (stagetime % t_interval1 == 0)
					{
						prev_stage_time = timer;
						stage = DECEL;
					}
				}
				if (stage == DECEL)
				{
					stagetime = timer - prev_stage_time;
					get_real_velocity(encoder, stagetime);
					for (i = 0; i < 3; i++)
					{
						diff[i] = e_vel[i] - 0;
						if (diff[i] < 0)
						{
							speed[i] += ACONST*diff[i];
						}
						else if (diff[i] > 0)
						{
							speed[i] -= ACONST*diff[i];
						}
					}
					motor_control(MOTOR1, speed[0]);
					motor_control(MOTOR2, speed[1]);
					motor_control(MOTOR3, speed[2]);
					if (stagetime % t_interval2 == 0)
					{
						prev_stage_time = timer;
						stage = STOP;
					}
				}
			if (stage == STOP)
			{
				stagetime = timer - prev_stage_time;
				for (i = 0; i < 3; i++)
				{
					speed[i] = 0;
				}
				motor_control(MOTOR1, speed[0]);
				motor_control(MOTOR2, speed[1]);
				motor_control(MOTOR3, speed[2]);
				if (stagetime % 200 == 0)
				{
					counter++;
					if (counter == 5)
					{
						prev_stage_time = timer;
						stage == UTURN;
					}
					else if (counter < 5)
					{
						prev_stage_time = timer;
						stage == ACCEL;
					}
					else if (counter == 6)
					{
						prev_stage_time = timer;
						stage == END;
					}
				}
			}
			if (stage == UTURN)
			{
				stagetime = timer - prev_stage_time;
				for (i = 0; i < 3; i++)
				{
					speed[i] = x;
				}
				motor_control(MOTOR1, speed[0]);
				motor_control(MOTOR2, speed[1]);
				motor_control(MOTOR3, speed[2]);
				if (stagetime %  == 0)
				{
					prev_stage_time = timer;
					stage = LONGACC;
				}
			}
			if (stage == LONGACC)
			{
				stagetime = timer - prev_stage_time;
				get_real_velocity(encoder, stagetime);
				for (i = 0; i < 3; i++)
				{
					diff[i] = e_vel[i] - speed[i];
					if (diff[i] < 0)
					{
						speed[i] += ACONST*diff[i];
					}
					else if (diff[i] > 0)
					{
						speed[i] -= ACONST*diff[i];
					} 
					motor_control(MOTOR1, -speed[0]);
					motor_control(MOTOR2, -speed[1]);
					motor_control(MOTOR3, -speed[2]);
				}
				if (stagetime %  == 0)
				{
					prev_stage_time = timer;
					stage = LONGDEC;
				}
			}
			if (stage == LONGDEC) //flip direction!
			{
				stagetime = timer - prev_stage_time;
				get_real_velocity(encoder, stagetime);
				for (i = 0; i < 3; i++)
				{
					diff[i] = e_vel[i] - speed[i];
					if (diff[i] < 0)
					{
						speed[i] += ACONST*diff[i];
					}
					else if (diff[i] > 0)
					{
						speed[i] -= ACONST*diff[i];
					}
					motor_control(MOTOR1, -speed[0]);
					motor_control(MOTOR2, -speed[1]);
					motor_control(MOTOR3, -speed[2]);
				}
				if (stagetime % t_interval2 == 0)
				{
					prev_stage_time = timer;
					stage = END;
				}
			}
			if (stage == END) //flip direction!
			{
				stagetime = timer - prev_stage_time;
			}
			case 2: //manual mode
				//listener
		}
	}
	
}

int get_real_velocity(*encoder,stagetime)
{
	for (i = 0; i < 3; i++)
	{
		encoder[i] = get_count(i);
	}

	for (i = 0; i < 3; i++)
	{
		e_vel[i] = encoder[i]/stagetime;
	}
}
