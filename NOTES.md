# NOTES

My notes for working with various third-party libraries, system APIs and
tools used by this project.

## Useful links

### Ctags

[Generate](ctags -R --c++-kinds=+p --fields=+iaS --extra=+q /usr/include)

### DNS

#### `resolv(2)`

Code examples and documentation for using `res_query` and related methods.

[`dns_resolve.cc` code from Ceph project](https://github.com/ceph/ceph/blob/master/src/common/dns_resolve.cc)
[O'Reilly Networking book on using `res_*` and `ns_*` methods](https://docstore.mik.ua/orelly/networking_2ndEd/dns/ch15_02.htm)
[Example #1 of extracting IP address from A answer](https://github.com/fxstar/Linux/blob/67cfea7027e97b01bdf2030108fabee611d5b986/C/Cpluspluss/DnsRecords/DnsMx1.cpp)
[Example #2 of extracting IP address from A answer](https://oracleoam.blogspot.com/2014/08/gethostbyname-vs-resquery.html)

### Json

[JsonCpp Documentation](https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html)
[JsonCpp Wiki](https://en.wikibooks.org/wiki/JsonCpp#Examples_of_work_with_objects_and_arrays)
