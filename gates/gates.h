#ifndef COMSUM_GATES_GATES_H_
#define COMSUM_GATES_GATES_H_

#include <vector>
#include <stdio.h>

namespace gate {
	
	typedef enum volt {
		low_v,
		high_v
	} volt;
	
	class Input {
	public:
		virtual void input(volt input) = 0;
		virtual volt get() = 0;
		virtual ~Input() {}
	};

	class Output {
	public:
		virtual void output(volt out) = 0;
		virtual ~Output() {}
	};
	
	class LogOutput : public Output {
	public:
		virtual void output(volt out) {
			printf("result = %d\n", out);
		}
	};

	class ManualInput : public Input {
	public:
		ManualInput(): m_cache(low_v) {}
		virtual void input(volt in) {
			this->m_cache = in;
		}

		virtual volt get() {
			return this->m_cache;
		}
	private:
		volt m_cache;
	};

	class IGate {
	public:
		IGate(): m_output(nullptr) {}
		virtual void addInput(Input *input) = 0;
		virtual void setOutput(Output *output);
		virtual volt check() = 0;
	protected:
		Output *m_output;
	};
	
	class Bridge : public virtual ManualInput, public virtual Output {
	public:
		virtual void input(volt input);
		virtual volt get();
		virtual void output(volt out);
	};

	class SingleInputGate : public IGate {
	public:
		SingleInputGate(): m_input(nullptr) {}
		virtual void addInput(Input *input);
	protected:
		Input * m_input;
	};

	class MultInputGate : public IGate {
	public:
		virtual void addInput(Input *input);
	protected:
		std::vector<Input *> m_inputs;
	};

	class AndGate : public MultInputGate {
	public:
		virtual volt check();
	};

	class OrGate : public MultInputGate {
	public:
		virtual volt check();
	};

	class NotGate : public SingleInputGate {
	public:
		virtual volt check();
	};
	
	class NAndGate : public MultInputGate {
	public:
		NAndGate();
		virtual volt check();
		virtual void addInput(Input *input);
		virtual void setOutput(Output *output);
	private:
		AndGate m_andgate;
		NotGate m_notgate;	
	};
	
	class NOrGate : public MultInputGate {
	public:
		NOrGate();
		virtual volt check();
		virtual void addInput(Input *input);
		virtual void setOutput(Output *output);
	private:
		OrGate m_orgate;
		NotGate m_notgate;	
	};
}

#endif
