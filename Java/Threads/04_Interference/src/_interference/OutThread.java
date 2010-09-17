/*
 * 
 * 
 */
package _interference;

/**
 *
 * @author batas2
 */
public class OutThread implements Runnable {

    private Integer _c;

    public OutThread(Integer c) {
        _c = c;
    }

    @Override
    public void run() {
        while(true){
            System.out.println(_c);
        }
    }
}
