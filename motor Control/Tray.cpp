if(Ch2 >= 15){
	if(abs(Tray.rotation(deg)) < 100) 
		Tray.spin(fwd, Ch2, pct);
	else
		Tray.spin(fwd, Ch2 * 0.1, pct);
}
else if(Ch2 <= -15){
	Tray.spin(fwd, Ch2, pct);
}
else{
	Tray.stop(brake);
}
