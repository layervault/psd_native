require 'spec_helper'

describe 'Util' do
  it "pad2's correctly" do
    expect(PSD::Util.pad2(0)).to eq 0
    expect(PSD::Util.pad2(1)).to eq 2
  end

  it "pad4's correctly" do
    expect(PSD::Util.pad4(0)).to eq 4
    expect(PSD::Util.pad4(1)).to eq 4
    expect(PSD::Util.pad4(2)).to eq 4
  end
end