[![Version](https://badgen.net/pub/v/cbl_flutter)](https://pub.dev/packages/cbl_flutter)
[![License](https://badgen.net/pub/license/cbl_flutter)](https://github.com/cbl-dart/cbl-dart/blob/main/packages/cbl_flutter/LICENSE)
[![CI](https://github.com/cbl-dart/cbl-dart/actions/workflows/ci.yaml/badge.svg)](https://github.com/cbl-dart/cbl-dart/actions/workflows/ci.yaml)
[![codecov](https://codecov.io/gh/cbl-dart/cbl-dart/branch/main/graph/badge.svg?token=XNUVBY3Y39)](https://codecov.io/gh/cbl-dart/cbl-dart)

Couchbase Lite is an embedded, NoSQL database:

- **Multi-Platform** - Android, iOS, macOS, Windows, Linux
- **Standalone Dart and Flutter** - No manual setup required, just add the
  package.
- **Fast and Compact** - Uses efficient persisted data structures.

It is fully featured:

- **JSON Style Documents** - No explicit schema and supports deep nesting.
- **Expressive Queries** - N1QL (SQL for JSON), QueryBuilder, Full-Text Search
- **Observable** - Get notified of changes in database, queries and data sync.
- **Data Sync** - Pull and push data from/to server with full control over
  synced data.

---

❤️ If you find this package useful, please ⭐ us on [pub.dev][cbl] and
[GitHub][repository]. 🙏

🐛 & ✨ Did you find a bug or have a feature request? Please open a [GitHub
issue][issues].

👋 Do you you have a question or feedback? Let us know in a [GitHub
discussion][discussions].

---

**What are all these packages for?**

Couchbase Lite can be used with **standalone Dart** or with **Flutter** apps and
comes in two editions: **Community** and **Enterprise**.

Regardless of the app platform and edition of Couchbase Lite you use, you always
need the `cbl` package. All of the APIs of Couchbase Lite live in this package.

What other packages you need depends on the app platform and the edition of
Couchbase Lite you use.

| Package          | Required when you want to:                                                                                 | Pub                                          | Likes                                           | Points                                           | Popularity                                           |
| ---------------- | ---------------------------------------------------------------------------------------------------------- | -------------------------------------------- | ----------------------------------------------- | ------------------------------------------------ | ---------------------------------------------------- |
| [cbl]            | use Couchbase Lite.                                                                                        | ![](https://badgen.net/pub/v/cbl)            | ![](https://badgen.net/pub/likes/cbl)           | ![](https://badgen.net/pub/points/cbl)           | ![](https://badgen.net/pub/popularity/cbl)           |
| [cbl_dart]       | use the **Community** or **Enterprise Edition** in a **standalone Dart** app or in **Flutter unit tests**. | ![](https://badgen.net/pub/v/cbl_dart)       | ![](https://badgen.net/pub/likes/cbl_dart)      | ![](https://badgen.net/pub/points/cbl_dart)      | ![](https://badgen.net/pub/popularity/cbl_dart)      |
| [cbl_flutter]    | use Couchbase Lite in a **Flutter app**.                                                                   | ![](https://badgen.net/pub/v/cbl_flutter)    | ![](https://badgen.net/pub/likes/cbl_flutter)   | ![](https://badgen.net/pub/points/cbl_flutter)   | ![](https://badgen.net/pub/popularity/cbl_flutter)   |
| [cbl_flutter_ce] | use the **Community Edition** in a Flutter app.                                                            | ![](https://badgen.net/pub/v/cbl_flutter_ce) |                                                 |                                                  |                                                      |
| [cbl_flutter_ee] | use the **Enterprise Edition** in a Flutter app.                                                           | ![](https://badgen.net/pub/v/cbl_flutter_ee) |                                                 |                                                  |                                                      |
| [cbl_sentry]     | integrate Couchbase Lite with Sentry in a Dart or Flutter app.                                             | ![](https://badgen.net/pub/v/cbl_sentry)     | ![](https://badgen.net/pub/likes/cbl_sentry)    | ![](https://badgen.net/pub/points/cbl_sentry)    | ![](https://badgen.net/pub/popularity/cbl_sentry)    |
| [cbl_generator]  | generate Dart code to access data trough a typed data model.                                               | ![](https://badgen.net/pub/v/cbl_generator)  | ![](https://badgen.net/pub/likes/cbl_generator) | ![](https://badgen.net/pub/points/cbl_generator) | ![](https://badgen.net/pub/popularity/cbl_generator) |

# 🎯 Platform Support

|     Platform | Version                |
| -----------: | :--------------------- |
|          iOS | >= 10.0                |
|        macOS | >= 10.14               |
|      Android | >= 22                  |
| Linux **\*** | == Ubuntu 20.04-x86_64 |
|      Windows | >= 10                  |

**\***: 🐛 Currently broken because of a
[bug in Flutter](https://github.com/flutter/flutter/issues/66575). Most notably,
operations trying to return an error crash the app.

# 🔌 Getting started

1. Add [`cbl`][cbl] and `cbl_flutter` as dependencies:

   ```yaml
   dependencies:
     cbl: ...
     cbl_flutter: ...
   ```

2. Select the edition of Couchbase Lite you want to use, by adding as a
   dependency either [`cbl_flutter_ce`](https://pub.dev/packages/cbl_flutter_ce)
   for the Community Edition or
   [`cbl_flutter_ee`](https://pub.dev/packages/cbl_flutter_ee) for the
   Enterprise Edition:

   ```yaml
   # This dependency selects the Couchbase Lite Community Edition.
   cbl_flutter_ce: ...
   ```

   > ⚖️ You need to comply with the Couchbase licensing terms of the edition of
   > Couchbase Lite you select.

3. Make sure you have set the required minimum target version in the build
   systems of the platforms you support.

4. Initialize Couchbase Lite before using it:

   ```dart
   import 'dart:io';

   import 'package:cbl_flutter/cbl_flutter.dart';
   import 'package:cbl_flutter_ce/cbl_flutter_ce.dart';

   Future<void> initCouchbaseLite() async {
     await CouchbaseLiteFlutter.init();
   }
   ```

# Default database directory

When opening a database without specifying a directory,
[`path_provider`][path_provider]'s `getApplicationSupportDirectory` is used to
resolve it. See that function's documentation for the concrete locations on the
various platforms.

# 🧪 Flutter unit tests

Flutter unit tests are executed by a headless version of Flutter, on the
development host.

You can use the `cbl` package in your unit tests, but you need to use
[`cbl_dart`][cbl_dart] to initialize Couchbase Lite, instead of `cbl_flutter`:

```dart
import 'dart:io';

import 'package:cbl/cbl.dart';
import 'package:cbl_dart/cbl_dart.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  setUpAll(() async {
    // If no `filesDir` is specified when initializing CouchbaseLiteDart, the
    // working directory is used as the default database directory.
    // By specifying a `filesDir` here, we can ensure that the tests don't
    // create databases in the project directory.
    final tempFilesDir = await Directory.systemTemp.createTemp();
    await CouchbaseLiteDart.init(edition: Edition.community, filesDir: tempFilesDir.path);
  });

  test('use a database', () async {
    final db = await Database.openAsync('test');
    await db.saveDocument(MutableDocument({'message': 'Hello, World!'}));
    await db.close();
  });
}
```

Unit tests are the best way to **learn, experiment and validate ideas**, since
they launch much quicker than integration tests. Be aware though, that using
Couchbase Lite like this **cannot replace integration testing** your database
code on actual devices or even simulators.

These tests can validate that you're using Couchbase Lite correctly and the code
works as expected generally, but subtle differences between platforms, operating
system versions and devices can still crop up.

# 💡 Where to go next

- Check out the example app in the **Example** tab.
- Look at the usage examples for [`cbl`][cbl].

# ⚖️ Disclaimer

> ⚠️ This is not an official Couchbase product.

[repository]: https://github.com/cbl-dart/cbl-dart
[path_provider]: https://pub.dev/packages/path_provider
[cbl]: https://pub.dev/packages/cbl
[cbl_dart]: https://pub.dev/packages/cbl_dart
[cbl_flutter]: https://pub.dev/packages/cbl_flutter
[cbl_flutter_ce]: https://pub.dev/packages/cbl_flutter_ce
[cbl_flutter_ee]: https://pub.dev/packages/cbl_flutter_ee
[cbl_sentry]: https://pub.dev/packages/cbl_sentry
[cbl_generator]: https://pub.dev/packages/cbl_generator
[issues]: https://github.com/cbl-dart/cbl-dart/issues
[discussions]: https://github.com/cbl-dart/cbl-dart/discussions
[sync gateway]: https://www.couchbase.com/sync-gateway
