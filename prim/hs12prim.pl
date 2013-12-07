use Math::NumSeq::ErdosSelfridgeClass;
$seq = Math::NumSeq::ErdosSelfridgeClass->new(on_values => '-');
while($i<50000000){
	$seq->next;
}