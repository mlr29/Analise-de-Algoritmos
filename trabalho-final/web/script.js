document.addEventListener('DOMContentLoaded', () => {
    const DATA_URL = 'resultados.json';

    // utility: generate distinct colors
    function colorForIndex(i) {
        const colors = [
            '#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd', '#8c564b',
            '#e377c2', '#7f7f7f', '#bcbd22', '#17becf'
        ];
        return colors[i % colors.length];
    }


    // status element para mensagens ao usuário
    let statusEl = document.getElementById('status');
    if (!statusEl) {
        statusEl = document.createElement('div');
        statusEl.id = 'status';
        document.body.insertBefore(statusEl, document.body.firstChild);
    }

    // cria canvas se não existir (index.html já fornece um canvas preferencialmente)
    let canvas = document.getElementById('myChart');
    if (!canvas) {
        canvas = document.createElement('canvas');
        canvas.id = 'myChart';
        canvas.style.maxWidth = '1000px';
        canvas.style.maxHeight = '600px';
        document.body.appendChild(canvas);
    }

    fetch(DATA_URL)
        .then(res => {
            if (!res.ok) throw new Error('Falha ao carregar ' + DATA_URL + ': ' + res.status);
            return res.text();
        })
        .then(text => {
            const obj = JSON.parse(text);
            // validar e notificar
            if (!Array.isArray(obj.resultados)) {
                console.error('Formato inesperado em', DATA_URL, obj);
                if (statusEl) statusEl.textContent = 'Formato inesperado do JSON (esperado um array). Veja o console.';
                return;
            }
            if (statusEl) statusEl.textContent = `JSON carregado: ${obj.resultados.length} objeto(s). Preparando gráfico...`;

            // labels: usar 1..N a partir do maior iteracoes/tempos encontrado (ou campo iteracoes)
            let maxLen = 0;
            obj.resultados.forEach(o => {
                const len = (o.iteracoes && Number(o.iteracoes) > 0) ? Number(o.iteracoes) : (o.tempos ? o.tempos.length : 0);
                if (len > maxLen) maxLen = len;
            });
            const labels = Array.from({ length: maxLen }, (_, i) => (i + 1).toString());

            const datasets = obj.resultados.map((o, idx) => {
                const label = (o.algoritmo || 'alg') + (o.tipo ? ' (' + o.tipo + ')' : '');
                const raw = (o.tempos || []).map(v => Number(v));
                // se iteracoes for maior que raw.length, pad com nulls para manter alinhamento
                const targetLen = (o.iteracoes && Number(o.iteracoes) > 0) ? Number(o.iteracoes) : raw.length;
                // converter segundos -> milissegundos e ajustar comprimento
                const data = raw.slice(0, targetLen).map(v => (v === null || isNaN(v)) ? null : v * 1000.0);
                while (data.length < targetLen) data.push(null);
                console.log(`dataset[${idx}] label='${label}' len=${data.length} sample=`, data.slice(0,6));
                return {
                    label,
                    data,
                    fill: false,
                    borderColor: colorForIndex(idx),
                    backgroundColor: colorForIndex(idx),
                    tension: 0.2,
                    pointRadius: 1
                };
            });

            // --- calcular estatísticas para cada dataset ---
            function getNumbersFromData(arr) {
                return arr.filter(v => v !== null && !isNaN(v));
            }

            function computeStats(nums) {
                if (!nums || nums.length === 0) return null;
                const n = nums.length;
                let sum = 0;
                let min = nums[0], max = nums[0];
                const freq = new Map();
                for (const v of nums) {
                    sum += v;
                    if (v < min) min = v;
                    if (v > max) max = v;
                    // contar moda com arredondamento para 6 casas para agrupar flutuantes muito próximos
                    const key = Number(v).toFixed(6);
                    freq.set(key, (freq.get(key) || 0) + 1);
                }
                const mean = sum / n;
                // desvio padrão amostral
                let sq = 0;
                for (const v of nums) sq += (v - mean) * (v - mean);
                const variance = n > 1 ? sq / (n - 1) : 0;
                const stddev = Math.sqrt(variance);
                // moda
                let mode = null; let modeCount = 0;
                for (const [k, c] of freq.entries()) {
                    if (c > modeCount) { modeCount = c; mode = Number(k); }
                }
                return { min, max, mean, stddev, mode, count: n };
            }

            const statsArray = datasets.map(ds => {
                const nums = getNumbersFromData(ds.data);
                return { label: ds.label, stats: computeStats(nums) };
            });

            // renderizar tabela de estatísticas
            let statsEl = document.getElementById('stats');
            if (!statsEl) {
                statsEl = document.createElement('div');
                statsEl.id = 'stats';
                canvas.parentNode.insertBefore(statsEl, canvas.nextSibling);
            }
            // construir HTML da tabela
            let html = '<h3>Estatísticas por série (ms)</h3>';
            html += '<table style="border-collapse:collapse;width:100%">';
            html += '<thead><tr><th style="border:1px solid #ccc;padding:6px;text-align:left">Série</th>' +
                    '<th style="border:1px solid #ccc;padding:6px">N</th>' +
                    '<th style="border:1px solid #ccc;padding:6px">Mín</th>' +
                    '<th style="border:1px solid #ccc;padding:6px">Máx</th>' +
                    '<th style="border:1px solid #ccc;padding:6px">Média</th>' +
                    '<th style="border:1px solid #ccc;padding:6px">Moda</th>' +
                    '<th style="border:1px solid #ccc;padding:6px">Desvio Padrão</th></tr></thead><tbody>';
            for (const s of statsArray) {
                const st = s.stats;
                if (!st) {
                    html += `<tr><td style="border:1px solid #ddd;padding:6px">${s.label}</td><td colspan="6" style="border:1px solid #ddd;padding:6px">sem dados</td></tr>`;
                } else {
                    html += `<tr>` +
                        `<td style="border:1px solid #ddd;padding:6px">${s.label}</td>` +
                        `<td style="border:1px solid #ddd;padding:6px;text-align:right">${st.count}</td>` +
                        `<td style="border:1px solid #ddd;padding:6px;text-align:right">${st.min.toFixed(3)}</td>` +
                        `<td style="border:1px solid #ddd;padding:6px;text-align:right">${st.max.toFixed(3)}</td>` +
                        `<td style="border:1px solid #ddd;padding:6px;text-align:right">${st.mean.toFixed(3)}</td>` +
                        `<td style="border:1px solid #ddd;padding:6px;text-align:right">${st.mode !== null ? st.mode.toFixed(3) : '—'}</td>` +
                        `<td style="border:1px solid #ddd;padding:6px;text-align:right">${st.stddev.toFixed(3)}</td>` +
                        `</tr>`;
                }
            }
            html += '</tbody></table>';
            statsEl.innerHTML = html;

            if (datasets.length === 0) {
                if (statusEl) statusEl.textContent = 'Nenhum dataset encontrado no JSON.';
                console.warn('Nenhum dataset para plotar. obj=', obj.resultados);
                return;
            }

            // configurar Chart.js
            // espera que Chart.js já esteja carregado no documento (via CDN ou bundle)
            if (typeof Chart === 'undefined') {
                console.error('Chart.js não encontrado. Inclua Chart.js no HTML antes de script.js.');
                return;
            }

            // destruir gráfico anterior se existir
            if (canvas._chartInstance) {
                canvas._chartInstance.destroy();
            }

            const ctx = canvas.getContext('2d');
            canvas._chartInstance = new Chart(ctx, {
                type: 'line',
                data: {
                    labels,
                    datasets
                },
                options: {
                    responsive: true,
                    plugins: {
                        legend: { position: 'top' },
                        title: { display: true, text: 'Tempos por iteração' },
                        tooltip: {
                            callbacks: {
                                label: function(context) {
                                    const v = context.parsed.y;
                                    if (v === null || typeof v === 'undefined') return '';
                                    return context.dataset.label + ': ' + v.toFixed(3) + ' ms';
                                }
                            }
                        }
                    },
                    scales: {
                        y: {
                            type: 'linear',
                            title: { display: true, text: 'Tempo (ms)' },
                            beginAtZero: true,
                            ticks: {
                                callback: function(value) {
                                    return Number(value).toFixed(3) + ' ms';
                                }
                            }
                        },
                        x: {
                            title: { display: true, text: 'Iteração / Tamanho' }
                        }
                    }
                }
            });
        if (statusEl) statusEl.textContent = `Gráfico renderizado (${datasets.length} série(s)). (Coleção: ${obj.tamanhoColecao} elementos)`;
        })
        .catch(err => {
            console.error('Erro ao processar dados para o gráfico:', err);
        });
});
