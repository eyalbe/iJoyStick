package eyal.remote;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.EditText;

public class MainActivity extends Activity implements SensorEventListener,
		OnTouchListener {

	// public final static String EXTRA_MESSAGE =
	// "com.example.myfirstapp.MESSAGE";
	private ComHandler com;
	// private MotionHandler handler;
	// private String s;
	private SensorManager manager;
	private Sensor accel;
	private Sensor magnetic;
	private float[] mValuesMagnet = new float[3];
	private float[] mValuesAccel = new float[3];
	private float[] mValuesOrientation = new float[3];
	private float[] mRotationMatrix = new float[9];
	private double degrees;
	private int value;
	private double tilt;
	private Menu myMenu;
	private int currentMenu = 0;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main2);
		com = new ComHandler();
		EditText msgText = (EditText)findViewById(R.id.msgText);
		manager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		accel = manager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		magnetic = manager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
		degrees = 180 / Math.PI;
		msgText.setText("Please enter the server ip address.");
	}

	@Override
	public void onResume() {
		super.onResume();
		if(currentMenu == 1){
			manager.registerListener(this, accel,SensorManager.SENSOR_DELAY_FASTEST);
			manager.registerListener(this, magnetic,SensorManager.SENSOR_DELAY_FASTEST);
		}
	}

	@Override
	public void onPause() {
		super.onPause();
		if(currentMenu == 1){
			manager.unregisterListener(this, accel);
			manager.unregisterListener(this, magnetic);
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		myMenu = menu;
		return true;
	}

	@Override
	public void onSensorChanged(SensorEvent event) {
		if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER)
			System.arraycopy(event.values, 0, mValuesAccel, 0, 3);
		if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD)
			System.arraycopy(event.values, 0, mValuesMagnet, 0, 3);
		SensorManager.getRotationMatrix(mRotationMatrix, null, mValuesAccel,
				mValuesMagnet);
		SensorManager.getOrientation(mRotationMatrix, mValuesOrientation);
		tilt = (degrees * mValuesOrientation[1] * 1.3);
		if (tilt > 90)
			tilt = 90;
		if (tilt < -90)
			tilt = -90;
		value = (int) ((tilt / 90) * 16500);
		com.send("1" + (16500 - value));
	}

	@Override
	public void onAccuracyChanged(Sensor arg0, int arg1) {
		// TODO Auto-generated method stub

	}

	private class Connect extends AsyncTask<String, Integer, Integer> {
		@Override
		protected Integer doInBackground(String... params) {
			if (com.connect(params[0]) == true)
				return 0;
			else
				return 1;
		}
	}

	@Override
	public boolean onTouch(View v, MotionEvent event) {
		if(currentMenu == 1){
			if(event.getAction() == MotionEvent.ACTION_DOWN)
				buttonsCom.send("31" + v.getTag());
			if(event.getAction() == MotionEvent.ACTION_UP)
				buttonsCom.send("30" + v.getTag());
		}
		if(currentMenu == 2){
			if(event.getAction() == MotionEvent.ACTION_DOWN)
				buttonsCom.send("51" + v.getTag());
			if(event.getAction() == MotionEvent.ACTION_UP)
				buttonsCom.send("50" + v.getTag());
		}
		return false;
	}
	
	public void start(View view){
		EditText text = (EditText)findViewById(R.id.text);
		EditText msgText = (EditText)findViewById(R.id.msgText);
		String ip = text.getText().toString();
		new Connect().execute(ip);
		int i = 0;
		while(!com.isConnected){
			try {Thread.sleep(100);} catch (InterruptedException e) {}
			i++;
			if(i == 20)
				break;
		}
		if(!com.isConnected)
			msgText.setText("Could't connect to server. try again.");
		else{
			msgText.setText("Connection established.");
			try {Thread.sleep(1000);} catch (InterruptedException e) {}
			manager.registerListener(this, accel,SensorManager.SENSOR_DELAY_FASTEST);
			manager.registerListener(this, magnetic,SensorManager.SENSOR_DELAY_FASTEST);
			setContentView(R.layout.activity_main1);
			currentMenu = 1;
			findViewById(R.id.button1).setOnTouchListener(this);
			findViewById(R.id.button2).setOnTouchListener(this);
			findViewById(R.id.button3).setOnTouchListener(this);
			findViewById(R.id.button4).setOnTouchListener(this);
			findViewById(R.id.pedal1).setOnTouchListener(this);
			findViewById(R.id.pedal2).setOnTouchListener(this);
			getMenuInflater().inflate(R.menu.menu, myMenu);
		}
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
	    // Handle item selection
	    switch (item.getItemId()) {
	        case R.id.op1:
	        	currentMenu = 1;
	        	setContentView(R.layout.activity_main1);
	        	manager.registerListener(this, accel,SensorManager.SENSOR_DELAY_FASTEST);
				manager.registerListener(this, magnetic,SensorManager.SENSOR_DELAY_FASTEST);
				findViewById(R.id.button1).setOnTouchListener(this);
				findViewById(R.id.button2).setOnTouchListener(this);
				findViewById(R.id.button3).setOnTouchListener(this);
				findViewById(R.id.button4).setOnTouchListener(this);
				findViewById(R.id.pedal1).setOnTouchListener(this);
				findViewById(R.id.pedal2).setOnTouchListener(this);
	            return true;
	        case R.id.op2:
	        	currentMenu = 2;
	        	setContentView(R.layout.activity_main3);
	        	manager.unregisterListener(this, accel);
	    		manager.unregisterListener(this, magnetic);
				findViewById(R.id.up).setOnTouchListener(this);
				findViewById(R.id.down).setOnTouchListener(this);
				findViewById(R.id.right).setOnTouchListener(this);
				findViewById(R.id.left).setOnTouchListener(this);
				findViewById(R.id.esc).setOnTouchListener(this);
				findViewById(R.id.ent).setOnTouchListener(this);
	            return true;
	        default:
	            return super.onOptionsItemSelected(item);
	    }
	}
}
