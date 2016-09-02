#include "gates.h"

namespace gate {
	void Bridge::input(volt input) {
		printf("this function shouldn't be invoked\n");
	}

	volt Bridge::get() {
		return ManualInput::get();
	}

	void Bridge::output(volt out) {
		ManualInput::input(out);
	}
	
	void IGate::setOutput(Output *output) {
		if(this->m_output) {
			delete this->m_output;
		}
		this->m_output = output;
	}
	
	void SingleInputGate::addInput(Input *input) {
		if(this->m_input) {
			delete this->m_input;
		}
		this->m_input = input;
	}

	void MultInputGate::addInput(Input *input) {
		this->m_inputs.push_back(input);
	}

	volt AndGate::check() {
		int ret = high_v;
		std::vector<Input *>::iterator it = this->m_inputs.begin();
		for(; it != this->m_inputs.end(); ++it) {
			ret &= (int)((*it)->get());
		}
		volt v_ret = (volt)ret;
		m_output->output(v_ret);
		return v_ret;
	}

	volt OrGate::check() {
		int ret = low_v;
		std::vector<Input *>::iterator it = this->m_inputs.begin();
		for(; it != this->m_inputs.end(); ++it) {
			ret |= (int)((*it)->get());
		}
		volt v_ret = (volt)ret;
		m_output->output(v_ret);
		return v_ret;
	}

	volt NotGate::check() {
		volt ret = this->m_input->get() == high_v ? low_v : high_v;
		m_output->output(ret);
		return ret;
	}
	
	NAndGate::NAndGate() {
		Bridge *bridge = new Bridge();
		this->m_andgate.setOutput(bridge);
		this->m_notgate.addInput(bridge);
	}
	
	volt NAndGate::check() {
		volt ret0 = this->m_andgate.check();
		return this->m_notgate.check();
	}

	void NAndGate::addInput(Input *input) {
		this->m_andgate.addInput(input);
	}

	void NAndGate::setOutput(Output *output) {
		this->m_notgate.setOutput(output);
	}

	NOrGate::NOrGate() {
		Bridge *bridge = new Bridge();
		this->m_orgate.setOutput(bridge);
		this->m_notgate.addInput(bridge);
	}
	
	volt NOrGate::check() {
		volt ret0 = this->m_orgate.check();
		return this->m_notgate.check();
	}

	void NOrGate::addInput(Input *input) {
		this->m_orgate.addInput(input);
	}

	void NOrGate::setOutput(Output *output) {
		this->m_notgate.setOutput(output);
	}
}
