import { Key, KeyboardModifier, QKeySequence, QObject, QObjectSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';

/**
 * Define one global hot key.
 *
 * Once registered, the `activated` event will be fired whenever the user
 * presses the key, regardless of which application is focused.
 */
export class QHotkey extends QObject<QHotkeySignals> {
    constructor(shortcut: QKeySequence);
    constructor(shortcut: QKeySequence, autoRegister: boolean);
    constructor(keyCode: Key, modifiers: KeyboardModifier, autoRegister: boolean);
    constructor(arg1: QKeySequence|Key, arg2?: boolean| KeyboardModifier, arg3?: boolean) {
        if (arg1 instanceof QKeySequence) {
          const shortcut = arg1;
          const autoRegister = Boolean(arg2 ?? false);
          super(new addon.QHotkey(shortcut.native, autoRegister));
          return;
        }

        const keyCode = <Key> arg1;
        const modifiers = <KeyboardModifier> arg2;
        const autoRegister = Boolean(arg3 ?? false);
        super(new addon.QHotkey(keyCode, modifiers, autoRegister));
    }

    /**
     * Returns true if the shortcut is active and ready to emit events.
     *
     * @return True if the shortcut is registered
     */
    isRegistered(): boolean {
        return this.native.isRegistered();
    }

    /**
     * Register or deregister the shortcut
     *
     * @param registered True to register, false to deregister.
     *
     */
    setRegistered(registered: boolean): boolean {
        return this.native.setRegistered(registered);
    }
}
wrapperCache.registerWrapper('QHotkeyWrap', QHotkey);

export interface QHotkeySignals extends QObjectSignals {
    activated: () => void;
    released: () => void;
}
