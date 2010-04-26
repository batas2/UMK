/*
 * 
 * 
 */
package _interference;

/**
 *
 * @author batas2
 */
public class InterferenceThread implements Runnable {

    private Counter _c;

    public InterferenceThread(Counter c) {
        _c = c;
    }

    @Override
    public void run() {
        for (int i = 1; i <= 10; i++) {
            _c.increment();
        }
    }
}

