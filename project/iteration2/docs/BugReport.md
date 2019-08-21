##Bug Report

**Not Complete:**
1. Accepts method for each event of each sensor:
	Accept works for distress and entity but not proximity sensor.
2. The proximity sensor is visual but, from what i got from lab 4. The
	sensor stays at the front of the robot but does not follow the 
	heading_angle.
3. Registered sensors in the arena:
	I attempted to have a check for entity distress, entity, and proximity. But 
	i kept getting multiple errors and my code did not compile completely.
4. Proximity Sensor/Event:
	I completed the classes but was not completelt sure how to implement the range or
	to call the function to the arena.
5. Distress Sensor/Event:
	I have the distress switch going off when colliding with the player but i have been able to
	implement the event distress in my arena do to compiling errors. The functionality of to the 
	event and the sensor are there but its functionality in the arena isnt complete/not working
6. Entity Sensor/Event:
	i wasnt able to complete the implementation of the range and distance of the entity sensor to
	return what time of entity enters its radius.The functionality of to the 
	event and the sensor are there but its functionality in the arena isnt complete/not working

**Not Functional:**
1. SuperBot has been made but is not functional:
	I wasnt able to figure out how to remove the robot from the vector to make it a superbot.
	To fix it, all i need to do is correctly pop the robot from the vector and create a new 
	superbot taking in that robot's params before it is deleted.
2. Win is implemented but a loss is not.
	Once superbot is implemented it is a simple check to see if the robot count you started with
	is equivalent to the amount of current superbots.

3. Indepth sensor tests


**Not Attempted:**
1. Robot unfreezing other robots.

2. Robot sensing a distress call.


**Others:**
There also might be bugs that i have yet to encounter in my own personal testing
