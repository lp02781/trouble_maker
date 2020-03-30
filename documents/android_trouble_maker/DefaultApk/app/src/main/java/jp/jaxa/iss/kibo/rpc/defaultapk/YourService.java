package jp.jaxa.iss.kibo.rpc.defaultapk;

import jp.jaxa.iss.kibo.rpc.api.KiboRpcService;

/**
 * Class meant to handle commands from the Ground Data System and execute them in Astrobee
 */

import gov.nasa.arc.astrobee.Result;
import gov.nasa.arc.astrobee.types.Point;
import gov.nasa.arc.astrobee.types.Quaternion;

public class YourService extends KiboRpcService {
    @Override
    protected void runPlan1(){
        api.judgeSendStart();

        moveToWrapper(10.6, -4.3, 5, 0, 0, -0.7071068, 0.7071068);
        Bitmap snapshot = api.getBitmapNavCam();
        String valueX = "...";
        api.judgeSendDiscoveredQR(0, valueX);
        moveToWrapper(11, -4.3, 5, 0, 0, -0.7071068, 0.7071068);
        moveToWrapper(11, -5.7, 5, 0, 0, -0.7071068, 0.7071068);
        moveToWrapper(11.5, -5.7, 4.5, 0, 0, 0, 1);
        moveToWrapper(11, -6, 5.55, 0, -0.7071068, 0, 0.7071068);
        String markerId = "...";
        api.judgeSendDiscoveredAR(markerId);
        api.laserControl(true);
        moveToWrapper(11.1, -6, 5.55, 0, -0.7071068, 0, 0.7071068);

        api.judgeSendFinishSimulation();
        sendData(MessageType.JSON, "data", "SUCCESS:defaultapk runPlan1");
    }

    @Override
    protected void runPlan2(){
        // write here your plan 2
    }

    @Override
    protected void runPlan3(){
        // write here your plan 3
    }

    private void moveToWrapper(double pos_x, double pos_y, double pos_z,
                               double qua_x, double qua_y, double qua_z,
                               double qua_w){

        final int LOOP_MAX = 3;
        final Point point = new Point(pos_x, pos_y, pos_z);
        final Quaternion quaternion = new Quaternion((float)qua_x, (float)qua_y,
                (float)qua_z, (float)qua_w);

        Result result = api.moveTo(point, quaternion, true);

        int loopCounter = 0;
        while(!result.hasSucceeded() || loopCounter < LOOP_MAX){
            result = api.moveTo(point, quaternion, true);
            ++loopCounter;
        }
    }

    public String doInBackground(Bitmap mp){
        String decodText;
        int width = mp.getWidth();
        int height = mp.getHeight();
        int[] pixels = new int[width*height];
        mp.getPixels(pixels, 0, width, 0, 0,width, height);
        RGBLuminanceSource source = new RGBLuminanceSource(width, height, pixels);
        final Reader = new QRCodeReader();
        try {
            final com.google.zxing.Result result = new MultiFormatReader().decode(new BinaryBitmap(new HybridBinarizer(source)));
            decodText = result.getText();
        } catch (Exception e){
            decodText = "";
        }
        return decodText;
    }

    public String qr_pos_p11(){
        moveToWrapper(11.5, -5.7, 4.5, 0,0,0,1);
        bitmap bm = api.getBitmapNavCam();
        log.d(TAG, "Bitmap bm:"+bm);
        bitmap bm = api.getBitmapNavCam();
        log.d(TAG, "Bitmap bn:"+bn);
        String valueQZ = doInbackground(bm);
        String valueQ = doInBackground(bn);
        String re = "";
        if(valueQZ.length()>0) {
            re = valueQZ;
        } else if(valueQ.length()>0){
            re = valueQ;
        }
        else {
            log.d(TAG, "QR Code Error");
        }
        return re;
    }
}

