import 'async_callback.dart';
import 'base.dart';
import 'blob.dart';
import 'dart_finalizer.dart';
import 'database.dart';
import 'document.dart';
import 'fleece.dart';
import 'libraries.dart';
import 'logging.dart';
import 'query.dart';
import 'replicator.dart';

/// Wether to use the `isLeaf` flag when looking up native functions.
const useIsLeaf = true;

abstract class Bindings {
  Bindings(Bindings parent) : libs = parent.libs {
    parent._children.add(this);
  }

  Bindings.root(this.libs);

  final DynamicLibraries libs;

  List<Bindings> get _children => [];
}

class CBLBindings extends Bindings {
  CBLBindings(LibrariesConfiguration config)
      : super.root(DynamicLibraries.fromConfig(config)) {
    base = BaseBindings(this);
    asyncCallback = AsyncCallbackBindings(this);
    dartFinalizer = DartFinalizerBindings(this);
    logging = LoggingBindings(this);
    database = DatabaseBindings(this);
    document = DocumentBindings(this);
    mutableDocument = MutableDocumentBindings(this);
    query = QueryBindings(this);
    resultSet = ResultSetBindings(this);
    blobs = BlobsBindings(this);
    replicator = ReplicatorBindings(this);
    fleece = FleeceBindings(this);
  }

  static CBLBindings? _instance;

  static CBLBindings get instance {
    final instance = _instance;
    if (instance == null) {
      throw StateError('CBLBindings have not been initialized.');
    }

    return instance;
  }

  static CBLBindings? get maybeInstance => _instance;

  static void init(LibrariesConfiguration libraries) =>
      _instance ??= CBLBindings(libraries);

  late final BaseBindings base;
  late final AsyncCallbackBindings asyncCallback;
  late final DartFinalizerBindings dartFinalizer;
  late final LoggingBindings logging;
  late final DatabaseBindings database;
  late final DocumentBindings document;
  late final MutableDocumentBindings mutableDocument;
  late final QueryBindings query;
  late final ResultSetBindings resultSet;
  late final BlobsBindings blobs;
  late final ReplicatorBindings replicator;
  late final FleeceBindings fleece;
}
