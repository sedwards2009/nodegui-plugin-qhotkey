import { QMainWindow, QLabel, QKeySequence } from '@nodegui/nodegui';
import { QHotkey } from './main';

class Demo {

  #f1: QHotkey = null;
  #f2: QHotkey = null;
  // Note: We will need this to keep the QHotkey instance alive and prevent
  //       garage collection while the application runs.

  run(): void {
    const win = new QMainWindow();
    win.setWindowTitle('QHotkey Demo');

    const label = new QLabel(win);
    label.setText('Press a F1 or F2');
    win.setCentralWidget(label);
    win.show();

    this.#f1 = new QHotkey(new QKeySequence('F1'), true);
    this.#f1.addEventListener('activated', () => {
      console.log('F1 activated!');
      label.setText('Press a F1 or F2: You pressed F1!');
    });
    this.#f2 = new QHotkey(new QKeySequence('F2'), true);
    this.#f2.addEventListener('activated', () => {
      console.log('F2 activated!');
      label.setText('Press a F1 or F2: You pressed F2!');
    });
  }
}

const demo = new Demo();
demo.run();
(global as any).demo = demo;
