* README

Hierarchy of types for the Tiger language, with (most of) their
interfaces.


ostream& operator<<(ostream& ostr, const Type& t)
bool operator==(const Type& lhs, const Type& rhs);
bool operator!=(const Type& lhs, const Type& rhs);

/Type/
    virtual ~Type() {}
    virtual const Type& actual() const;
    virtual bool compatible_with(const Type& other) const;
    virtual void accept(ConstVisitor& v) const;
    virtual void accept(Visitor& v);

  Nil
    bool compatible_with(const Type& other) const override;
    const Type* record_type_get() const;
    void set_record_type(const Type& type) const;

  Void

  Int

  String

  Named(const misc::symbol& name, const Type* type)
    const Type* type_get() const;
    void type_set(const Type *type);
    void type_set(const Type *type) const;
    misc::symbol name_get() const;
    void name_set(const misc::symbol& name);
    const Type& actual() const override;
    const bool sound() const;
    bool compatible_with(const Type& other) const override;

  Array(const Type& type)
    const Type& type_get() const;

  Record()
    const Type* field_type(const misc::symbol& key) const;
    int field_index(const misc::symbol& key) const;
    const list<Field> fields_get() const;
    void field_add(const Field& field);
    void field_add(const misc::symbol& name, const Type& type);
    const_iterator begin() const;
    const_iterator end() const;

  Class(const Class* super = nullptr)
    const Type* attr_type(const misc::symbol& key) const;
    const Type* meth_type(const misc::symbol& key) const;
    const attrs_type& attrs_get() const;
    const meths_type& meths_get() const;
    const Attribute* attr_find(const misc::symbol& key) const;
    const Attribute* owner_attr_find(const misc::symbol& key) const;
    const Method* owned_meth_find(const misc::symbol& key) const;
    void attr_add(const Attribute& attr);
    void attr_add(const VarDec* def);
    void meth_add(const Method* method);
    bool has_data() const;
    unsigned id_get() const;
    const Class* super_get() const;
    void super_set(const Class* type);
    const subclasses_type& subclasses_get() const;
    void subclass_add(const Class* subclass) const;
    void subclasses_clear() const;
    const Class* common_root(const Class& other) const;
    bool sound() const;
    static const Class& object_instance();

  Function(const Record* formals, const Type& result)

    Method(const misc::symbol& name, const Class* owner, const Record* formals,
           const Type& result, MethodDec* def)
      misc::symbol name_get() const;
      const Class* owner_get() const;
      const Type& type_get() const;
      const MethodDec* def_get() const;
      MethodDec* def_get();
      void name_set(const misc::symbol& name);
      void def_set(MethodDec* def);

Field(misc::symbol name, const Type& type)
    misc::symbol name_get() const;
    const Type& type_get() const;

Attribute(const ast::VarDec* def)
    misc::symbol name_get() const;
    const Type& type_get() const;
    const ast::VarDec* def_get() const;
    void def_set(const ast::VarDec* def);
