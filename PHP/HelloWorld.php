<?php
$nama = "Nino";
$umur = 16;
$tinggi = "158 CM";
$berat = "Berat tidak diketahui.";
$kelas = "10.5";
$mapelf = "MTK, Informatika, IPA";

echo '<div style="
    text-align: center; 
    font-size: 22px; 
    background: linear-gradient(135deg, #667eea, #764ba2);
    color: white; 
    height: 100vh; 
    margin: 0; 
    display: flex; 
    justify-content: center; 
    align-items: center; 
    flex-direction: column; 
    font-family: \'Segoe UI\', Tahoma, Geneva, Verdana, sans-serif;
    box-shadow: inset 0 0 50px rgba(0,0,0,0.3);
    padding: 20px;
    border-radius: 15px;
    width: 90vw;
    max-width: 400px;
    margin-left: auto;
    margin-right: auto;
">';
echo "<p><strong>Nama:</strong> $nama</p>";
echo "<p><strong>Umur:</strong> $umur tahun</p>";
echo "<p><strong>Tinggi:</strong> $tinggi</p>";
echo "<p><strong>Berat badan:</strong> $berat</p>";
echo "<p><strong>Kelas:</strong> $kelas</p>";
echo "<p><strong>Mata pelajaran favorit:</strong> $mapelf</p>";
echo "<br>";
echo "<h2>Halo, $nama!</h2>";
echo '</div>';
?>
