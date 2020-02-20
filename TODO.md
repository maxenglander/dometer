 TODO
 ====
  [x] move dns/server/\*event\* to dns/event
  [x] move dns/server/\*handler\* to dns/handler
  [ ] replace #include statements with forward declarations
  [ ] create internal boundaries (e.g. ::internal or ::detail)
  [x] use "canonical" project structure (e.g. dometer/dometer)
  [x] move x/ to std/x
  [ ] move prometheus extensions to prometheus/x
  [ ] use cpp convention/style enforcer
  [ ] move dns/\*.{c,h}pp to dns/packet/
  [ ] extract dns/packet::make\* methods to separate class
  [ ] remove unused deps from build files
