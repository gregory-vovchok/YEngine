#ifndef SETPRIVATETILEACTION_H
#define SETPRIVATETILEACTION_H
#include <Engine/Core/Trigger/Action/AbstractAction.h>
#include <Engine/Core/Parser/Variable/StringVariable/StringVariable.h>
#include <Engine/Core/Trigger/StringExprParserEx/StringExprParserEx.h>
class SetPrivateAssetAction: public AbstractAction
{
	friend class Trigger;
	friend class AbstractAction;
	private: StringANSI targetName;
	private: StringExprParserEx templateTarget;
	private: MagicPointer<AbstractObject> target;
	private: SetPrivateAssetAction(void);
	private: SetPrivateAssetAction(int32 _type);
	public: virtual ~SetPrivateAssetAction(void);
	public: virtual void SetVariableArg(int32 _index, StringANSI _name);
	public: virtual void SetTemplateArg(int32 _index, StringANSI _expr);
	public: virtual StringANSI GetTemplateArg(int32 _index);
	public: virtual StringANSI GetVariableArg(int32 _index);
	public: virtual void operator () (void);
	private: void TemplateTargetIsCompleted(void);
	private: void TargetIsLost(void);
	private: void TemplateTargetIsChanged(void);
	private: void ObjectIsDestroyed(AbstractObject* _object);
	private: void TargetIsRenamed(AbstractObject::NameInfo* _info);
	private: void ObjectIsCreated(AbstractObject* _object);
	private: void UpdateValid(void);
	public: virtual bool SaveToFile(StringANSI _path = "");
	public: virtual bool SaveToFile(File& _file);
	private: static AbstractAction* _LoadFromFile(File& _file);
};



#endif 