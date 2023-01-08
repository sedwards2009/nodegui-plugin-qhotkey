# nodegui-plugin-qhotkey

[NodeGui](https://github.com/nodegui/nodegui) plugin which uses QHotKey for global hotkey support.

TypeScript example:

```typescript
//...
import { QHotkey } from 'nodegui-plugin-qhotkey';

//...

const f1 = new QHotkey(new QKeySequence('F1'), true);
const f1.addEventListener('activated', () => {
  console.log('F1 activated!');
  label.setText('Press a F1 or F2: You pressed F1!');
});

```


Install via NPM:

```
npm install nodegui-plugin-qhotkey
```

For the API see [src/index.ts](src/index.ts)

For a complete demo see [src/demo.ts](src/demo.ts)


# Maintainer

Simon Edwards <simon@simonzone.com>

# License

MIT

This software also contains parts of [QHotkey](https://github.com/Skycoder42/QHotkey). These parts are copyright 2016, Felix Barz and distributed under the 3 clause BSD license. See the `LICENSE` file in the `QHotkey-1.5.0` directory.

# Release Process (for maintainers)

* Make sure the version in `package.json` is correct.
* Tag the version with git (format: v1.2.3).
* Push the tag to origin.
* Wait for GitHub Action to build and release to NPM.
